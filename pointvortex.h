#ifndef POINTVORTEX_H
#define POINTVORTEX_H

#include<QVector>
#include<cmath>


class PointVortex
{
private:
    static const double Pi;

    QVector<double> x;
    QVector<double> y;
    double omega;

    static void f(const int& n, const QVector<PointVortex>& vortex, const double* yy, double* K);
    static double f_d(const double& x1, const double& x2, const double& y1, const double& y2);

public:
    PointVortex();
    PointVortex(double x_0, double y_0, double omega_0);
    ~PointVortex();

    void put(double x_0, double y_0, double omega_0);

    QVector<double> get_x();
    QVector<double> get_y();
    double get_x_i(int i);
    double get_y_i(int i);
    double get_omega();

    static void RK6(QVector<PointVortex>& vortex, const int& n, const int& t_end, const double& h);
    static double error_ForQ(const QVector<PointVortex>& vortex, const int& t_end, const double& h);
    static double error_ForP(const QVector<PointVortex>& vortex, const int& t_end, const double& h);
    static double error_ForI(const QVector<PointVortex>& vortex, const int& t_end, const double& h);
};

#endif // POINTVORTEX_H
