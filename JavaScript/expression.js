"use strict";

var names = ["x", "y", "z"];

var operation = function(h) {
    return function() {
        var args = arguments;
        return function() {
            var ans = [];
            for (var i = 0; i < args.length; ++i) {
                ans[i] = args[i].apply(null, arguments);
            }
            return h.apply(null, ans);
        }
    }
};

var cnst = function(val) {
    return function() {
        return val;
    }
};

var variable = function(name) {
    var i = names.indexOf(name);
    return function() {
        return arguments[i];
    }
};

var pi = cnst(Math.PI);
var e = cnst(Math.E);

var x = variable("x");
var y = variable("y");
var z = variable("z");

var min3 = operation(function() {
    return Math.min.apply(null, arguments);
});

var max5 = operation(function() {
    return Math.max.apply(null, arguments);
});

var add = operation(function(l, r) {
    return l + r;
});

var subtract = operation(function(l, r) {
    return l - r;
});

var multiply = operation(function(l, r) {
    return l * r;
});

var divide = operation(function(l, r) {
    return l / r;
});

var negate = operation(function (x) {
    return -x;
});

var parse = function(expr) {
    var tokens = expr.trim().split(/\s+/);
    var calculate = function() {
        var token = tokens.pop();
        if ((/\b-?\d+\b/).test(token)) {
            return cnst(+token);
        }
        if (names.indexOf(token) >= 0) {
            return variable(token);
        }
        switch (token) {
            case "e":
                return e;
            case "pi":
                return pi;
            case "min3":
                var vars = [];
                for (var i = 0; i < 3; ++i) {
                    vars[i] = calculate();
                }
                return min3.apply(null, vars);
            case "max5":
                var vars = [];
                for (var i = 0; i < 5; ++i) {
                    vars[i] = calculate();
                }
                return max5.apply(null, vars);
            case "+":
            case "-":
            case "*":
            case "/":
                var l, r;
                r = calculate();
                l = calculate();
                switch (token) {
                    case "+":
                        return add(l, r);
                    case "-":
                        return subtract(l, r);
                    case "*":
                        return multiply(l, r);
                    case "/":
                        return divide(l, r);
                    default:
                        return undefined;
                }
            case "negate":
                return negate(calculate());
            default:
                return undefined;
        }
    };
    return calculate();
};
