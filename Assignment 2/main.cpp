#include <bits/stdc++.h>
using namespace std;
#define double long double

// This is the Main Function of the Assignment.

vector<double> stimulate(vector<vector<double>> prob, int t0, int t1, int t2, double alpha, double gamma, double rho, double epsilon, int T)
{
    double beta = prob[1][2] + prob[1][3];

    double S_old = 1.0, E_old = 0.0, Ia_old = 0.0, Is_old = 0.0, R_old = 0.0, V_old = 0.0, D_old = 0.0;
    double S_new = 1.0, E_new = 0.0, Ia_new = 0.0, Is_new = 0.0, R_new = 0.0, V_new = 0.0, D_new = 0.0;
    double P_sv = 0.0, P_ei = beta;

    for (int t_current = 1; t_current <= T; ++t_current)
    {
        S_new = S_old - prob[0][1] * S_old - P_sv * S_old + prob[5][0] * V_old;
        E_new = E_old + prob[0][1] * S_old - P_ei * E_old;
        Ia_new = Ia_old + rho * P_ei * E_old - prob[2][4] * Ia_old - prob[2][6] * Ia_old;
        Is_new = Is_old + (1 - rho) * P_ei * E_old - prob[3][4] * Is_old - prob[3][6] * Is_old;
        R_new = R_old + prob[2][4] * Ia_old + prob[3][4] * Is_old;
        V_new = V_old + P_sv * S_old - prob[5][0] * V_old;
        D_new = D_old + prob[2][6] * Ia_old + prob[3][6] * Is_old;

        if (t_current >= t0)
        {
            P_sv = alpha * (t_current - t0);
            double sum = prob[0][0] + prob[0][1];
            prob[0][0] = (1 - P_sv) * prob[0][0] / sum;
            prob[0][1] = (1 - P_sv) * prob[0][1] / sum;
        }

        if (t_current >= t1 && t_current <= t2)
        {
            P_ei = gamma * beta;
        }
        else
        {
            P_ei = beta;
        }

        prob[1][1] = 1 - P_ei;

        prob[0][0] -= epsilon * (sin(2 * M_PI * t_current / 365));
        prob[0][1] += epsilon * (sin(2 * M_PI * t_current / 365));

        S_old = S_new;
        E_old = E_new;
        Ia_old = Ia_new;
        Is_old = Is_new;
        R_old = R_new;
        V_old = V_new;
        D_old = D_new;
    }

    vector <double> v;
    v.push_back(S_new);
    v.push_back(E_new);
    v.push_back(Ia_new);
    v.push_back(Is_new);
    v.push_back(R_new);
    v.push_back(V_new);
    v.push_back(D_new);

    return v;
}

// Here you can give input and then call the function.
// int main()
// {
//     vector <vector <double>> prob(7, vector <double> (7));
//     for (int i=0; i<7; i++)
//     {
//         for (int j=0; j<7; j++)
//         {
//             cin >> prob[i][j];
//         }
//     }
//     int t0, t1, t2, T;
//     double alpha, gamma, rho, epsilon;
//     cin >> t0 >> t1 >> t2 >> alpha >> gamma >> rho >> epsilon >> T;
//     vector <double> ans=stimulate(prob, t0, t1, t2, alpha, gamma, rho, epsilon, T);

//     for (int i=0; i<7; i++)
//     {
//         cout << fixed << setprecision(15) << ans[i] << " ";  // Set Precision command is used to give answer upto more decimal places.
//     }
//     cout << endl;

//     return 0;
// }