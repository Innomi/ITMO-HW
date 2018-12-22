#include <fstream>

#define EPS 1e-4

using namespace std;

ifstream cin("markchain.in");
ofstream cout("markchain.out");

int main()
{
    unsigned int n;
    double matrix[100][100][101] = { 0 };
    cin >> n;
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            cin >> matrix[i][j][0];
        }
    }
    unsigned int kolyaNeOchen = 0;
    for (size_t k = 0; k < 100; ++k)
    {
        for (size_t l = 0; l < n; ++l)
        {
            for (size_t i = 0; i < n; ++i)
            {
                for (size_t j = 0; j < n; ++j)
                {
                    matrix[l][i][k + 1] += matrix[l][j][k] * matrix[j][i][k];
                }
            }
        }
        bool nikitaTozheNeOchen = true;
        for (size_t i = 0; i < n; ++i)
        {
			for (size_t j = 0; j < n; ++j)
			{
				if (matrix[i][j][k + 1] - matrix[i][j][k] > EPS)
				{
					nikitaTozheNeOchen = false;
					break;
				}
			}
			if (!nikitaTozheNeOchen)
			{
				break;
			}
		}
		if (nikitaTozheNeOchen)
		{
			kolyaNeOchen = k + 1;
			break;
		}
    }
    cout.precision(4);
    for (size_t i = 0; i < n; ++i)
    {
        cout << matrix[0][i][kolyaNeOchen] << endl;
    }
    return 0;
}
