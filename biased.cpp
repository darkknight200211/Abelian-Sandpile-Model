#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>

using namespace std;

int main()
{
    int sand[101][101], psand[101][101], ivolve, ad_grain, s, t;
    int g_sum = 0, sum = 0, m, n, mm, nn, sinkx, sinky, c, crit;
    //int u = 40, v = 50;
    int s1 = 0, s2 = 3, ss, tt, dx, dy;

    // seed for produing randome numbers
    srand(time(NULL));
    cout << time(NULL) << endl
         << endl;

    m = 100; // eter m = grid size - 1
    n = 0;

    mm = m - 1;
    nn = n + 1;

    // user enters details to run simulation
    cout << "enter relaxation iteration: ";
    cin >> ivolve;
    cout << endl;
    cout << "how many grains to add: ";
    cin >> ad_grain;
    cout << endl;
    cout << "enter sink coordinated (x,y): ";
    cin >> sinkx >> sinky;
    cout << endl;

    ofstream sp("site_plot");

    // producing inintial state with grain height equal to crit for all grids
    // and counting number of grains that are present
    ofstream i_con("initial_configuration"); // this file contains the initial
                                             // configuration of the grid
    crit = 3;

    for (int i = n; i <= m; i = i + 1)
    {
        for (int j = n; j <= m; j = j + 1)
        {
            sand[i][j] = crit;
            psand[i][j] = sand[i][j];
            // cout << i << "  " << j << "  " << sand[i][j] << endl;
            i_con << i << "  " << j << "  " << sand[i][j] << endl;
            g_sum = g_sum + sand[i][j];
        }
        // cout << endl;
        i_con << endl;
    }

    // following block of code is used for producing random initial config
    // for (int i = n; i <= m; i = i + 1)
    // {
    //     for (int j = n; j <= m; j = j + 1)
    //     {
    //         sand[i][j] = rand() % 4;
    //         cout << i << "  " << j << "  " << sand[i][j] << endl;
    //         i_con << i << "  " << j << "  " << sand[i][j] << endl;
    //         psand[i][j] = sand[i][j];
    //         g_sum = g_sum + sand[i][j];
    //     }
    //     cout << endl;
    //     i_con << endl;
    // }
    i_con.close();

    cout << g_sum << " " << float(g_sum) / float(pow(m + 1, 2)) << endl;

    ofstream d_ty("density_graph"); // creating a file to register density
    // variation as function of grains added
    d_ty << 0 << "  " << g_sum << " " << float(g_sum) / float(pow(m + 1, 2)) << endl;

    // now grain addition starts:

    ss = mm;
    tt = mm;

    for (int k = 1; k <= ad_grain; k = k + 1)
    {
        c = 0;
        cout << "added: " << k << endl;
        if (k == 1)
        {
            s = rand() % (ss + 1);
            t = rand() % (ss + 1);
            // s = 5;
            // t = 5;
        }

        else
        {
            int a = 7, wei_l = -a, wei_h = a;
            // dx = wei_l + floor(rand()*float(wei_h+1-wei_l));
            // dy = wei_l + floor(rand()*float(wei_h+1-wei_l));
            dx = rand()%a - ((a-1)/2);
            dy = rand()%a - ((a-1)/2);
            cout << dx << " " << dy << endl;
            s = ss + dx;
            t = tt + dy;
            if(s > m)
            {
                s = mm;
            }
            else if(s < n)
            {
                s = nn;
            }
            else
            {
                s = s;
            }

            if(t > m)
            {
                t = mm;
            }
            else if(t < n)
            {
                t = nn;
            }
            else
            {
                t = t;
            }

        }
        cout << "site: " << s << "  " << t << endl;
        sp << k << "   " << s << " " << t << endl;

        // s = u;
        // t = v;

        sand[s][t] = sand[s][t] + 1;

        // following block makes sure that after addition of grain particles
        // the system obtains relaxed state
        while (c < ivolve)
        {
            // cumulating differences between two iterations of the system
            sum = 0;
            for (int i = n; i <= m; i = i + 1)
            {
                for (int j = n; j <= m; j = j + 1)
                {
                    sum = sum + sand[i][j] - psand[i][j];
                }
            }
            // cout << c << "  " << sum << endl;

            // block for updating the psand array for keeping track of net change in
            // grain number in system
            for (int i = n; i <= m; i = i + 1)
            {
                for (int j = n; j <= m; j = j + 1)
                {
                    psand[i][j] = sand[i][j];
                }
            }

            g_sum = g_sum + sum;

            // following block performs the topplings, in case any
            for (int i = n; i <= m; i = i + 1)
            {
                for (int j = n; j <= m; j = j + 1)
                {
                    if (sand[i][j] >= 4)
                    { // if a site has 4 or more grains
                        sand[i][j] = sand[i][j] - 4;

                        if (i == n && j == n)
                        {
                            sand[i + 1][j] = sand[i + 1][j] + 1;
                            sand[i][j + 1] = sand[i][j + 1] + 1;
                        }
                        else if (i == n && j == m)
                        {
                            sand[i + 1][j] = sand[i + 1][j] + 1;
                            sand[i][j - 1] = sand[i][j - 1] + 1;
                        }
                        else if (i == m && j == m)
                        {
                            sand[i - 1][j] = sand[i - 1][j] + 1;
                            sand[i][j - 1] = sand[i][j - 1] + 1;
                        }
                        else if (i == m && j == n)
                        {
                            sand[i - 1][j] = sand[i - 1][j] + 1;
                            sand[i][j + 1] = sand[i][j + 1] + 1;
                        }
                        else if (i == n or i == m)
                        {
                            if (i == n)
                            {
                                sand[i + 1][j] = sand[i + 1][j] + 1;
                                sand[i][j + 1] = sand[i][j + 1] + 1;
                                sand[i][j - 1] = sand[i][j - 1] + 1;
                            }
                            else if (i == m)
                            {
                                sand[i - 1][j] = sand[i - 1][j] + 1;
                                sand[i][j + 1] = sand[i][j + 1] + 1;
                                sand[i][j - 1] = sand[i][j - 1] + 1;
                            }
                        }
                        else if (j == n or j == m)
                        {
                            if (j == n)
                            {
                                sand[i - 1][j] = sand[i - 1][j] + 1;
                                sand[i + 1][j] = sand[i + 1][j] + 1;
                                sand[i][j + 1] = sand[i][j + 1] + 1;
                            }
                            else if (j == m)
                            {
                                sand[i - 1][j] = sand[i - 1][j] + 1;
                                sand[i + 1][j] = sand[i + 1][j] + 1;
                                sand[i][j - 1] = sand[i][j - 1] + 1;
                            }
                        }
                        else
                        {
                            sand[i + 1][j] = sand[i + 1][j] + 1;
                            sand[i - 1][j] = sand[i - 1][j] + 1;
                            sand[i][j + 1] = sand[i][j + 1] + 1;
                            sand[i][j - 1] = sand[i][j - 1] + 1;
                        }
                    }
                    else if (sand[i][j] <= 3)
                    {
                        sand[i][j] = sand[i][j];
                    }

                    // if (i == sinkx && j == sinky)
                    // {
                    //     sand[i][j] = 0;
                    // }
                }
            }

            c = c + 1;
            // cout << endl;
        }

        //  if (k == ad_grain)
        //  {
            ofstream r_con("last_plot");
            for (int i = n; i <= m; i = i + 1)
            {
                for (int j = n; j <= m; j = j + 1)
                {
                    r_con << i << " " << j << " " << sand[i][j] << endl;
                    // cout << i << " " << j << " " << sand[i][j] << endl;
                }
                r_con << endl;
                // cout << endl;
            }
            r_con.close();
        // }

        cout << k << "  " << g_sum << " " << float(g_sum) / float(pow(m + 1, 2)) << endl;
        cout << "   " << endl;
        d_ty << k << "  " << g_sum << " " << float(g_sum) / float(pow(m + 1, 2)) << endl;

        ss = s;
        tt = t;
    }

    cout << endl
         << "fnial nummber: " << g_sum << endl;

    d_ty.close();
    sp.close();
    return 0;
}