#include <iostream>

using namespace std;

int main()
{
    freopen("postfixlogic.out", "w", stdout);
    cout << "2\nS 0 _ -> S _ > 0 >\nS 1 _ -> S _ > 1 >\nS o _ -> O _ ^ _ <\nS a _ -> A _ ^ _ <\nS _ _ -> E _ ^ _ <\n\nE _ 0 -> AC 0 ^ _ ^\nE _ 1 -> AC 1 ^ _ ^\n\nO _ 0 -> O0 _ ^ _ <\nO _ 1 -> O1 _ ^ _ <\nO0 _ 0 -> S _ > 0 >\nO0 _ 1 -> S _ > 1 >\nO1 _ 0 -> S _ > 1 >\nO1 _ 1 -> S _ > 1 >\n\nA _ 0 -> A0 _ ^ _ <\nA _ 1 -> A1 _ ^ _ <\nA0 _ 0 -> S _ > 0 >\nA0 _ 1 -> S _ > 0 >\nA1 _ 0 -> S _ > 0 >\nA1 _ 1 -> S _ > 1 >\n" << flush;
    return 0;
}
