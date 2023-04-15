#include <vector>
#include <string>
#include <iostream>
#include <cmath>

class shape 
{
public:
	virtual ~shape() {}
	virtual void print() = 0;
	virtual double area() = 0;
	virtual double volumn() = 0;
};
class two_D_shape: virtual public shape
{
public:
	virtual double area() = 0;
};
class three_D_shape :virtual public shape
{
public:
	virtual double area() = 0;
	virtual double volumn()=0;
};
class rectangle :public two_D_shape,public shape
{
private:
	double base;
	double height;
public:
	rectangle(double input_base, double input_height) { base = input_base; height = input_height; }
	~rectangle() {}
	double area();
	double volumn() { return 0; }
	void print();
};
class square :public two_D_shape, public shape
{
private:
	double base;
	double height;
public:
	square(double input_base, double input_height) { base = input_base; height = input_height; }
	~square() {}
	double area();
	double volumn() { return 0; }
	void print();
};
class ellipse :public two_D_shape, public shape
{
private:
	double radius_one;
	double radius_two;
public:
	ellipse(double input_radius_one, double input_radius_two) { radius_one = input_radius_one; radius_two = input_radius_two; }
	~ellipse() {}
	double area();
	double volumn() { return 0; }
	void print();
};
class circle :public two_D_shape, public shape
{
private:
	double radius;
public:
	circle(double input_radius) { radius = input_radius;}
	~circle() {}
	double area();
	double volumn() { return 0; }
	void print();
};

class cuboid :public three_D_shape, public shape
{
private:
	double x;
	double y;
	double z;
public:
	cuboid(double input_x, double input_y, double input_z) { x = input_x; y = input_y; z = input_z; }
	~cuboid() {}
	double area();
	double volumn();
	void print();
};
class cube :public three_D_shape, public shape
{
private:
	double x;
	double y;
	double z;
public:
	cube(double input_x, double input_y, double input_z) { x = input_x; y = input_y; z = input_z; }
	~cube() {}
	double area();
	double volumn();
	void print();
};
class ellipsoid :public three_D_shape, public shape
{
private:
	double radius_one;
	double radius_two;
	double radius_three;
public:
	ellipsoid(double input_radius_one, double input_radius_two, double input_radius_three) { radius_one = input_radius_one; radius_two = input_radius_two; radius_three = input_radius_three; }
	~ellipsoid() {}
	double area();
	double volumn();
	void print();
};
class sphere :public three_D_shape, public shape
{
private:
	double radius;
public:
	sphere(double input_radius) { radius = input_radius; }
	~sphere() {}
	double area();
	double volumn();
	void print();
};
double rectangle::area() 
{
	return base * height / 2;
}
void rectangle::print() 
{
	std::cout << "Rectangle has base " << base << " height " << height << std::endl;
}
double square::area()
{
	return base * height / 2;
}
void square::print()
{
	std::cout << "sqaure has base " << base << " height " << height << std::endl;
}
double ellipse::area()
{
	return 3.14159265358979323846 * radius_one * radius_two;
}
void ellipse::print()
{
	std::cout << "ellipse has radius one " << radius_one << " radius_two " << radius_two << std::endl;
}
double circle::area()
{
	return 3.14159265358979323846 * pow(radius,2);
}
void circle::print()
{
	std::cout << "circle has radius " << radius << std::endl;
}
double cuboid::area()
{
	return 2 * x * y + 2 * y * z + z * x * 2;
}
double cuboid::volumn()
{
	return x * y * z;
}
void cuboid::print()
{
	std::cout << "coboid has side one " << x << " side two " << y << " side three " << z << std::endl;
}
double cube::area()
{
	return 2 * x * y + 2 * y * z + z * x * 2;
}
double cube::volumn()
{
	return x * y * z;
}
void cube::print()
{
	std::cout << "cube has side one " << x << " side two " << y << " side three " << z << std::endl;
}
double ellipsoid::area()
{
	double axis_one = pow(radius_one*radius_two,1.6);
	double axis_two = pow(radius_one*radius_three,1.6);
	double axis_three = pow(radius_two*radius_three,1.6);
	return 4* 3.14159265358979323846*pow((axis_one+ axis_two+ axis_three)/3,1/1.6);
}
double ellipsoid::volumn()
{
	return 4 / 3 * 3.14159265358979323846 * radius_one * radius_two * radius_three;
}
void ellipsoid::print()
{
	std::cout << "ellipsoid has radius one " << radius_one << " radius two " << radius_two << " radius three " << radius_three << std::endl;
}
double sphere::area()
{
	return 4 * 3.14159265358979323846*pow(radius,2);
}
double sphere::volumn()
{
	return 4 / 3 * 3.14159265358979323846 * pow(radius, 3);
}
void sphere::print()
{
	std::cout << "sphere has radius " << radius << std::endl;
}
int main() 
{
	std::vector<shape*> shape_array;
	for (size_t i{ 0 }; i < 8; i++) 
	{
		shape* temp_shape;
		shape_array.push_back(temp_shape);
	}
	shape_array[0] = new rectangle(1, 2);
	shape_array[1] = new square(3, 4);
	shape_array[2] = new ellipse(5, 6);
	shape_array[3] = new circle(7);
	shape_array[4] = new cuboid(8, 9, 10);
	shape_array[5] = new cube(11, 12, 13);
	shape_array[6] = new ellipsoid(14, 15, 16);
	shape_array[7] = new sphere(17);

	for (size_t i{}; i < shape_array.size(); i++)
	{
		shape_array[i]->print();
		std::cout << "Area: " << shape_array[i]->area() << std::endl;
		std::cout << "Volumn: " << shape_array[i]->volumn() << std::endl;
	}
	shape_array.clear();
	std::cout << "The array is cleared, size:" << shape_array.size() << std::endl;



}