//
//  Shape.hpp
//  Rebel
//
//  Created by 云心逸 on 2019/3/23.
//  Copyright © 2019 云心逸. All rights reserved.
//

#ifndef Shape_hpp
#define Shape_hpp

#ifndef GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#endif

#include <vector>
#include <string>
#include <iostream>
#include <GLUT/GLUT.h>

struct Point {
	float x;
	float y;
	Point(float x, float y) : x(x), y(y) {}
	void move(float _x, float _y) {
		x += _x;
		y += _y;
	}
	std::string repr() const {
		return "point(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	}
};

struct Size {
	float width;
	float height;
	Size(float w, float h) : width(w), height(h) {}
};

struct Rect {
	union {
		int8_t colorv[4];
		int32_t color;
	};
	Point origin;
	Size msize;
	Rect(int32_t color, const Point& orig, const Size& sz) : color(color), origin(orig), msize(sz) {}
	Rect() : color(), origin(0, 0), msize(0, 0) {}
	Rect(const Rect& rhs) : color(rhs.color), origin(rhs.origin), msize(rhs.msize) {}
	std::string repr() const {
		std::string s("Rect((");
		s += std::to_string(origin.x) + ", " + std::to_string(origin.y) + ") : ";
		s += "[" + std::to_string(msize.width) + "x" + std::to_string(msize.height) + "])";
		return s;
	}
	void move(float x, float y) {
		origin.move(x, y);
	}
	void draw() const {
		glRectf(origin.x, origin.y, origin.x + msize.width, origin.y + msize.height);
	}
};

#endif /* Shape_hpp */
