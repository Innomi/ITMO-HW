#include <iostream>

using namespace std;

int main()
{
    freopen("infixlogic.out", "w", stdout);
    cout << "3\nS 0 _ _ -> S _ > 0 > _ ^\nS 1 _ _ -> S _ > 1 > _ ^\nS o _ _ -> O _ ^ _ ^ _ <\nS a _ _ -> A _ ^ _ ^ _ <\nS ( _ _ -> S _ > _ ^ ( >\nS ) _ _ -> B _ ^ _ ^ _ <\nS _ _ _ -> E _ ^ _ ^ _ <\n\nE _ _ o -> E _ ^ o > _ <\nE _ _ a -> E _ ^ a > _ <\nE _ _ _ -> R _ ^ _ < _ ^\n\nR _ 0 _ -> R _ ^ 0 < _ ^\nR _ 1 _ -> R _ ^ 1 < _ ^\nR _ o _ -> R _ ^ o < _ ^\nR _ a _ -> R _ ^ a < _ ^\nR _ _ _ -> CS _ ^ _ > _ ^\n\nO _ _ o -> O _ ^ o > _ <\nO _ _ a -> O _ ^ a > _ <\nO _ _ ( -> O _ ^ _ ^ ( >\nO _ _ _ -> S _ > _ ^ o >\n\nA _ _ o -> A _ ^ _ ^ o >\nA _ _ a -> A _ ^ a > _ <\nA _ _ ( -> A _ ^ _ ^ ( >\nA _ _ _ -> S _ > _ ^ a >\n\nB _ _ o -> B _ ^ o > _ <\nB _ _ a -> B _ ^ a > _ <\nB _ _ ( -> S _ > _ ^ _ ^\n\nCS _ 0 _ -> CS _ ^ _ > 0 >\nCS _ 1 _ -> CS _ ^ _ > 1 >\nCS _ o _ -> CO _ ^ _ ^ _ <\nCS _ a _ -> CA _ ^ _ ^ _ <\nCS _ _ _ -> CE _ ^ _ ^ _ <\n\nCE _ _ 0 -> AC 0 ^ _ ^ _ ^\nCE _ _ 1 -> AC 1 ^ _ ^ _ ^\n\nCO _ _ 0 -> CO0 _ ^ _ ^ _ <\nCO _ _ 1 -> CO1 _ ^ _ ^ _ <\nCO0 _ _ 0 -> CS _ ^ _ > 0 >\nCO0 _ _ 1 -> CS _ ^ _ > 1 >\nCO1 _ _ 0 -> CS _ ^ _ > 1 >\nCO1 _ _ 1 -> CS _ ^ _ > 1 >\n\nCA _ _ 0 -> CA0 _ ^ _ ^ _ <\nCA _ _ 1 -> CA1 _ ^ _ ^ _ <\nCA0 _ _ 0 -> CS _ ^ _ > 0 >\nCA0 _ _ 1 -> CS _ ^ _ > 0 >\nCA1 _ _ 0 -> CS _ ^ _ > 0 >\nCA1 _ _ 1 -> CS _ ^ _ > 1 >\n" << flush;
    return 0;
}
