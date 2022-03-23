# Assignment_1, part_1
#### The algorithim implimentation steps:

* first, I check the if the gradient is bigger than 1, or less than -1, or between 0 and 1, or between -1 and 0, in the first two cases I switch between x and y.
* second, I check the point and how I'll draw the line (from left to right or from right to left), if its from right to left, I switch between the two points.
* last, I check if there is reflection case, (in case of reflection, I decrease the value of y, or x, according to the case).

#### Code:

void Renderer::DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color)
{  

	int x0 = p1.x;    
	int y0 = p1.y;
	int x1 = p2.x;
	int y1 = p2.y;
	int dx = x1 - x0;
	int	dy = y1 - y0;
	if (abs(dy) < abs(dx)) {
		if (x1 > x0) {
			int yi = 1;
			if (dy < 0) {
				yi = -1;
				dy = -dy;
			}
			int D = -dx;
			int y = y0;
			int x = x0;
			while ( x <= x1) {
				if (D > 0) {
					y = y + yi;
					D = D - (2 * dx);
				}
				Renderer::PutPixel(x, y, color);
				D = D + 2 * dy;
				x++;
			}
		}
		else {
			dx = x0 - x1;
			dy = y0 - y1;
			int	yi = 1;
			if (dy < 0) {
				yi = -1;
				dy = -dy;
			}
			int D = -dx;
			int y = y1;
			int x = x1;
			while (x <= x0) {
				if (D > 0) {
					y = y + yi;
					D = D - (2 * dx);
				}
				Renderer::PutPixel(x, y, color);
				D = D + 2 * dy;
				x++;
			}
		}
	}
	else {
		if (y1 > y0) {
			int	xi = 1;
			if (dx < 0) {
				xi = -1;
				dx = -dx;
			}
			int D = -dy;
			int x = x0;
			int y = y0;
			while (y <= y1) {
				if (D > 0) {
					x = x + xi;
					D = D - (2 * dy);
				}
				PutPixel(x, y, color);
				D = D + 2 * dx;
				y++;
			}
		}
		else {
			dx = x0 - x1;
			dy = y0 - y1;
			int	xi = 1;
			if (dx < 0) {
				xi = -1;
				dx = -dx;
			}
			int D = -dy;
			int x = x1;
			int y = y1;
			while (y <= y0) {
				if (D > 0) {
					x = x + xi;
					D = D - (2 * dy);
				}
				PutPixel(x, y, color);
				D = D + 2 * dx;
				y++;
			}
		}
	}
	
}


#### A picture of the sanity check results:
![test1 Image](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment1Report/test1.png)

#### A drawing of my own choic:
![beatles Image](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment1Report/beatles.png)

