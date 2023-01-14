#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class Curve3D {
  public:
    virtual ~Curve3D() {}
    virtual std::pair<double, double> Point(double t) const = 0;
    virtual std::pair<double, double> Derivative(double t) const = 0;
};

class Circle3D : public Curve3D {
  public:
    Circle3D(double radius) : radius_(radius) {}
    std::pair<double, double> Point(double t) const override {
        return {radius_ * cos(t), radius_ * sin(t)};
    }
    std::pair<double, double> Derivative(double t) const override {
        return {-radius_ * sin(t), radius_ * cos(t)};
    }
    double radius() const { return radius_; }

  private:
    double radius_;
};

class Ellipse3D : public Curve3D {
  public:
    Ellipse3D(double a, double b) : a_(a), b_(b) {}
    std::pair<double, double> Point(double t) const override {
        return {a_ * cos(t), b_ * sin(t)};
    }
    std::pair<double, double> Derivative(double t) const override {
        return {-a_ * sin(t), b_ * cos(t)};
    }

  private:
    double a_, b_;
};

class Helix3D : public Curve3D {
  public:
    Helix3D(double radius, double pitch) : radius_(radius), pitch_(pitch) {}
    std::pair<double, double> Point(double t) const override {
        return {radius_ * cos(t), radius_ * sin(t), pitch_ * t};
    }
    std::pair<double, double> Derivative(double t) const override {
        return {-radius_ * sin(t), radius_ * cos(t), pitch_};
    }

  private:
    double radius_, pitch_;
};

int main() {
    std::vector<Curve3D*> curves;
    for (int i = 0; i < 10; i++) {
        if (i % 3 == 0) {
            curves.push_back(new Circle3D(i + 0.5));
        } else if (i % 3 == 1) {
            curves.push_back(new Ellipse3D(i + 0.5, i + 1.5));
            } else {
            curves.push_back(new Helix3D(i + 0.5, i + 2.5));
        }
    }

    std::cout << "Points and derivatives of all curves at t=PI/4:" << std::endl;
    const double t = M_PI / 4;
    for (auto curve : curves) {
        auto point = curve->Point(t);
        auto derivative = curve->Derivative(t);
        std::cout << "Point: (" << point.first << ", " << point.second << ")"
                  << " Derivative: (" << derivative.first << ", " << derivative.second << ")"
                  << std::endl;
    }

    std::vector<Circle3D*> circles;
    for (auto curve : curves) {
        auto circle = dynamic_cast<Circle3D*>(curve);
        if (circle) {
            circles.push_back(circle);
        }
    }

    std::sort(circles.begin(), circles.end(), [](const Circle3D* a, const Circle3D* b) {
        return a->radius() < b->radius();
    });

    std::cout << "Sorted circles by radius:" << std::endl;
    for (auto circle : circles) {
        std::cout << "Radius: " << circle->radius() << std::endl;
    }

    double total_radius = 0;
    for (auto circle : circles) {
        total_radius += circle->radius();
    }
    std::cout << "Total sum of radii: " << total_radius << std::endl;

    for (auto curve : curves) {
        delete curve;
    }

    return 0;
}