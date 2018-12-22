"use strict";

var names = ["x", "y", "z"];

var operation = function(f, op, diffFunc) {
    var proto = {};
    proto.evaluate = function() {
        var ans = [];
        for (var i = 0; i < this.argsAmount(); ++i) {
            ans[i] = this.args(i).evaluate.apply(this.args(i), arguments);
        }
        return f.apply(null, ans);
    };
    proto.toString = function() {
        var string = "";
        for (var i = 0; i < this.argsAmount(); ++i) {
            string += this.args(i).toString() + " ";
        }
        return string + op;
    };
    proto.prefix = function() {
        var string = "(" + op + " ";
        for (var i = 0; i < this.argsAmount() - 1; ++i) {
            string += this.args(i).prefix() + " ";
        }
        string += this.args(this.argsAmount() - 1).prefix();
        return string + ")";
    };
    proto.diff = function(v) {
        var ans = [];
        for (var i = 0; i < this.argsAmount(); ++i) {
            ans[i] = this.args(i).diff(v);
        }
        return diffFunc.apply(this, ans);
    };
    
    return function() {
        var funcArgs = arguments;
        this.args = function(num) {
            return funcArgs[num];
        };
        this.argsAmount = function() {
            return funcArgs.length;
        };
        this.__proto__ = proto;
    };
};

var protoVar = {};
protoVar.evaluate = function() {
    return arguments[names.indexOf(this.name())];
};
protoVar.toString = function() {
    return this.name();
};
protoVar.prefix = function() {
    return this.name();
};
protoVar.diff = function(name) {
    return new Const(this.name() == name ? 1 : 0);
};

var Variable = function(name) {
    var varName = name;
    this.name = function() {
        return varName;
    };
    this.__proto__ = protoVar;
};

var protoConst = {};
protoConst.evaluate = function() {
    return this.val();
};
protoConst.toString = function() {
    return this.val().toString();
};
protoConst.prefix = function() {
    return this.val().toString();
};
protoConst.diff = function() {
    return new Const(0);
};

var Const = function(val) {
    var constVal = val;
    this.val = function() {
        return constVal;
    };
    this.__proto__ = protoConst;
};

var Add = operation(function(l, r) {
    return l + r;
}, "+", function(l, r) {
    return new Add(l, r);
});

var Subtract = operation(function(l, r) {
    return l - r;
}, "-", function(l, r) {
    return new Subtract(l, r);
});

var Multiply = operation(function(l, r) {
    return l * r;
}, "*", function(l, r) {
    return new Add(
        new Multiply(this.args(1), l),
        new Multiply(this.args(0), r)
    );
});

var Divide = operation(function(l, r) {
    return l / r;
}, "/", function(l, r) {
    return new Divide(
        new Subtract(
            new Multiply(l, this.args(1)),
            new Multiply(r, this.args(0))
        ),
        new Multiply(this.args(1), this.args(1))
    );
});

var Negate = operation(function(x) {
    return -x;
}, "negate", function(x) {
    return new Negate(x);
});

var Sin = operation(function(x) {
    return Math.sin(x);
}, "sin", function(x) {
    return new Multiply(new Cos(this.args(0)), x);
});

var Cos = operation(function(x) {
    return Math.cos(x);
}, "cos", function(x) {
    return new Multiply(new Negate(new Sin(this.args(0))), x);
});

var Power = operation(function(val, pow) {
    return Math.pow(val, pow);
}, "pow", function(val, pow) {
    return new Add(
        new Multiply(
            new Multiply(
                this.args(1),
                new Power(
                    this.args(0),
                    new Subtract(
                        this.args(1),
                        new Const(1)
                    )
                )
            ),
            val
        ),
        new Multiply(
            new Multiply(
                new Power(
                    this.args(0),
                    this.args(1)
                ),
                pow
            ),
            new Log(
                new Const(Math.E),
                this.args(0)
            )
        )
    );
});

var Log = operation(function(base, val) {
    return Math.log(Math.abs(val)) / Math.log(Math.abs(base));
}, "log", function(base, val) {
    return new Divide(
        new Subtract(
            new Multiply(
                new Divide(
                    val,
                    this.args(1)
                ),
                new Log(
                    new Const(Math.E),
                    this.args(0)
                )
            ),
            new Multiply(
                new Divide(
                    base,
                    this.args(0)
                ),
                new Log(
                    new Const(Math.E),
                    this.args(1)
                )
            )
        ),
        new Power(
            new Log(
                new Const(Math.E),
                this.args(0)
            ),
            new Const(2)
        )
    );
});

var ops = {};
ops["+"] = {op: Add, args: 2};
ops["-"] = {op: Subtract, args: 2};
ops["*"] = {op: Multiply, args: 2};
ops["/"] = {op: Divide, args: 2};
ops["sin"] = {op: Sin, args: 1};
ops["cos"] = {op: Cos, args: 1};
ops["pow"] = {op: Power, args: 2};
ops["log"] = {op: Log, args: 2};
ops["negate"] = {op: Negate, args: 1};

var parse = function(expr) {
    var tokens = expr.trim().split(/\s+/);
    var calculate = function() {
        var token = tokens.pop();
        if ((/\b-?\d+\b/).test(token)) {
            return new Const(+token);
        }
        if (names.indexOf(token) >= 0) {
            return new Variable(token);
        }
        var args = [];
        for (var i = ops[token].args; i > 0; --i) {
            args[i - 1] = calculate();
        }
        var obj = {};
        ops[token].op.apply(obj, args);
        return obj;
    };
    return calculate();
};

var ParsePrefixError = function(message) {
    this.message = message;
    this.name = "ParsePrefixError";
    this.__proto__ = Error.prototype;
};

var parsePrefix = function(expr) {
    var regex = /([\(\)]|[A-Za-z]+|\-?\d+|[-+*/]+|\S+)/g;
    var lastArg = null;
    var lastIndex = 0;
    
    if (expr === "") {
        throw new ParsePrefixError("Empty input");
    }
    
    var expression = function(leftBracket) {
        var lIndex = regex.lastIndex;
        var token = regex.exec(expr);
        if (lastArg == null && token[0] != "(") {
            lastArg = token[0];
            lastIndex = lIndex;
        }
        if (token == null) {
            throw new ParsePrefixError("Unexpected end of expression");
        }
        var arg = token[0];
        if (arg.match(/\-?\d+/) != null) {
            if (leftBracket) {
                throw new ParsePrefixError("Expression expected, found " + arg + " at " + lastIndex);
            }
            return new Const(Number(arg));
        }
        if (names.indexOf(arg) >= 0) {
            if (leftBracket) {
                throw new ParsePrefixError("Expression expected, found " + arg + " at " + lastIndex);
            }
            return new Variable(arg);
        }
        switch (arg) {
            case "(":
                var res = expression(true);
                token = regex.exec(expr);
                if (token[0] !== ")") {
                    throw new ParsePrefixError("Too many arguments after " + lastArg + " at " + lastIndex);
                }
                return res;
            case ")":
                throw new ParsePrefixError("Too few arguments after " + lastArg + " at " + lastIndex);
        }
        if (!ops.hasOwnProperty(arg)) {
            throw new ParsePrefixError("Unknown symbol: " + arg + " at " + lastIndex);
        }
        if (leftBracket) {
            var args = [];
            for (var i = 0; i < ops[arg].args; i++) {
                args.push(expression(false));
            }
            var obj = {};
            ops[arg].op.apply(obj, args);
            return obj;
        } else {
            throw new ParsePrefixError("Expression expected, found " + arg + " at " + lastIndex);
        }
    }
    
    var res = expression(false);
    
    if (regex.exec(expr) != null) {
        throw new ParsePrefixError("Excess expression");
    }
    
    return res;
}
