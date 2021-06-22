#include "pointvortex.h"
#include <QDebug>

const double PointVortex::Pi= 3.14159265;

PointVortex::PointVortex(): omega(0.0)
{
    x.push_back(0.0);
    y.push_back(0.0);
}

PointVortex::PointVortex(double x_0, double y_0, double omega_0): omega(omega_0)
{
    x.push_back(x_0);
    y.push_back(y_0);
}

PointVortex::~PointVortex()
{
    x.clear();
    y.clear();
}

void PointVortex::put(double x_0, double y_0, double omega_0)
{
    x[0] = x_0;
    y[0] = y_0;
    omega = omega_0;
}

QVector<double> PointVortex::get_x()
{
    return x;
}

QVector<double> PointVortex::get_y()
{
    return y;
}

double PointVortex::get_x_i(int i)
{
    if (i < x.size()) {
        return x[i];
    }
    return -1;
}

double PointVortex::get_y_i(int i)
{
    if (i < y.size()) {
        return y[i];
    }
    return -1;
}

double PointVortex::get_omega()
{
    return omega;
}

inline double PointVortex::f_d(const double& x1, const double& x2, const double& y1, const double& y2)
{
    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

void PointVortex::f(const int& n, const QVector<PointVortex>& vortex, const double* yy, double* K)
{
    for (int i = 0; i < 2 * n; i++) {
        K[i] = 0;
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++)
        {
            if (i != k)
            {
                K[2 * k] += (-1 / (2 * Pi)) * vortex[i].omega * (yy[2 * k + 1] - yy[2 * i + 1])
                        / (pow(f_d(yy[2 * k], yy[2 * i], yy[2 * k + 1], yy[2 * i + 1]), 2));
                K[2 * k + 1] += (1 / (2 * Pi)) * vortex[i].omega * (yy[2 * k] - yy[2 * i])
                        / (pow(f_d(yy[2 * k], yy[2 * i], yy[2 * k + 1], yy[2 * i + 1]), 2));
            }
        }
    }
}

void PointVortex::RK6(QVector<PointVortex>& vortex, const int& n, const int& t_end, const double& h)
{
    double* yy = new double[2 * n];
    double* K1 = new double[2 * n];
    double* K2 = new double[2 * n];
    double* K3 = new double[2 * n];
    double* K4 = new double[2 * n];
    double* K5 = new double[2 * n];
    double* K6 = new double[2 * n];
    double* K7 = new double[2 * n];

    for (int i = 1; i < t_end / h; i++)
    {
        for (int k = 0; k < n; k++)
        {
            yy[2 * k] = vortex[k].x.back();
            yy[2 * k + 1] = vortex[k].y.back();
        }
        f(n, vortex, yy, K1);

        for (int k = 0; k < n; k++)
        {
            yy[2 * k] = vortex[k].x.back() + h * K1[2 * k] / 3.0;
            yy[2 * k + 1] = vortex[k].y.back() + h * K1[2 * k + 1] / 3.0;
        }
        f(n, vortex, yy, K2);

        for (int k = 0; k < n; k++)
        {
            yy[2 * k] = vortex[k].x.back() + h * K2[2 * k] * 2.0 / 3.0;
            yy[2 * k + 1] = vortex[k].y.back() + h * K2[2 * k + 1] * 2.0 / 3.0;
        }
        f(n, vortex, yy, K3);

        for (int k = 0; k < n; k++)
        {
            yy[2 * k] = vortex[k].x.back() + h * (K1[2 * k] / 12.0 + K2[2 * k] / 3.0 - K3[2 * k] / 12.0);
            yy[2 * k + 1] = vortex[k].y.back() + h * (K1[2 * k + 1] / 12.0 + K2[2 * k + 1] / 3.0
                    - K3[2 * k + 1] / 12.0);
        }
        f(n, vortex, yy, K4);

        for (int k = 0; k < n; k++)
        {
            yy[2 * k] = vortex[k].x.back() + h * (K1[2 * k] * 25.0 / 48.0 - K2[2 * k] * 55.0
                    / 24.0 + K3[2 * k] * 35.0 / 48.0 + K4[2 * k] * 15.0 / 8.0);
            yy[2 * k + 1] = vortex[k].y.back() + h * (K1[2 * k + 1] * 25.0 / 48.0 - K2[2 * k + 1] * 55.0
                    / 24.0 + K3[2 * k + 1] * 35.0 / 48.0 + K4[2 * k + 1] * 15.0 / 8.0);
        }
        f(n, vortex, yy, K5);

        for (int k = 0; k < n; k++)
        {
            yy[2 * k] = vortex[k].x.back() + h * (K1[2 * k] * 3.0 / 20.0 - K2[2 * k] * 11.0
                    / 20.0 - K3[2 * k] / 8.0 + K4[2 * k] / 2.0 + K5[2 * k] / 10.0);
            yy[2 * k + 1] = vortex[k].y.back() + h * (K1[2 * k + 1] * 3.0 / 20.0 - K2[2 * k + 1] * 11.0
                    / 20.0 - K3[2 * k + 1] / 8.0 + K4[2 * k + 1] / 2.0 + K5[2 * k + 1] / 10.0);
        }
        f(n, vortex, yy, K6);

        for (int k = 0; k < n; k++)
        {
            yy[2 * k] = vortex[k].x.back() + h * (-K1[2 * k] * 261.0 / 260.0 + K2[2 * k] * 33.0 / 13.0
                    + K3[2 * k] * 43.0 / 156.0 - K4[2 * k] * 118.0 / 39.0 + K5[2 * k] * 32.0 / 195.0
                    + K6[2 * k] * 80.0 / 39.0);
            yy[2 * k + 1] = vortex[k].y.back() + h * (-K1[2 * k + 1] * 261.0 / 260.0 + K2[2 * k + 1] * 33.0 / 13.0
                    + K3[2 * k + 1] * 43.0 / 156.0 - K4[2 * k + 1] * 118.0 / 39.0 + K5[2 * k + 1] * 32.0 / 195.0
                    + K6[2 * k + 1] * 80.0 / 39.0);
        }
        f(n, vortex, yy, K7);

        for (int k = 0; k < n; k++)
        {
            vortex[k].x.push_back(vortex[k].x.back() + (13.0 * K1[2 * k] + 55.0
                                  * K3[2 * k] + 55.0 * K4[2 * k] + 32.0
                    * K5[2 * k] + 32.0 * K6[2 * k] + 13.0 * K7[2 * k]) / 200.0 * h);
            vortex[k].y.push_back(vortex[k].y.back() + (13.0 * K1[2 * k + 1] + 55.0
                                  * K3[2 * k + 1] + 55.0 * K4[2 * k + 1] + 32.0
                    * K5[2 * k + 1] + 32.0 * K6[2 * k + 1] + 13.0 * K7[2 * k + 1]) / 200.0 * h);
        }
    }
    delete[] yy;
    delete[] K1;
    delete[] K2;
    delete[] K3;
    delete[] K4;
    delete[] K5;
    delete[] K6;
    delete[] K7;
}

double PointVortex::error_ForQ(const QVector<PointVortex> &vortex, const int &t_end, const double &h)
{
    double Q_min = 0.0;
    double Q_max = 0.0;
    double Q;
    for (int i = 0; i < t_end; i++)
    {
        Q = 0.0;
        for (int j = 0; j < vortex.size(); j++)
        {
            Q += vortex[j].omega * vortex[j].x[i/h];
        }
        if (i == 0)
        {
            Q_min = Q;
            Q_max = Q;
        }
        if (Q > Q_max)Q_max = Q;
        if (Q < Q_min)Q_min = Q;
    }
    return abs(Q_max - Q_min);
}

double PointVortex::error_ForP(const QVector<PointVortex> &vortex, const int &t_end, const double &h)
{
    double P_min = 0.0;
    double P_max = 0.0;
    double P;
    for (int i = 0; i < t_end; i++)
    {
        P = 0.0;
        for (int j = 0; j < vortex.size(); j++)
        {
            P += vortex[j].omega * vortex[j].y[i/h];
        }
        if (i == 0)
        {
            P_min = P;
            P_max = P;
        }
        if (P > P_max)P_max = P;
        if (P < P_min)P_min = P;
    }
    return abs(P_max - P_min);
}

double PointVortex::error_ForI(const QVector<PointVortex> &vortex, const int &t_end, const double &h)
{
    double I_min = 0.0;
    double I_max = 0.0;
    double I;
    for (int i = 0; i < t_end; i++)
    {
        I = 0.0;
        for (int j = 0; j < vortex.size(); j++)
        {
            I += vortex[j].omega * (vortex[j].x[i/h] * vortex[j].x[i/h] + vortex[j].y[i/h] * vortex[j].y[i/h]);
        }
        if (i == 0)
        {
            I_min = I;
            I_max = I;
        }
        if (I > I_max)I_max = I;
        if (I < I_min)I_min = I;
    }
    return abs(I_max - I_min);
}




