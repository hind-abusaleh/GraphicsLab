# Assignment_2, part_1
#### (1): 
The work was in - Renderer Class, the work is of two parts, the first was to implement the auxiliary functions that we will need for the task, and the second part is to implement the main function that we need to use.

The auxiliary functions (methods in Renderer Class) are:

1) float Renderer::get_triangle_area(int x1, int y1, int x2, int y2, int x3, int y3) :

A function for finding the area of a triangle, which receives the coordinates of the angles of the triangle.

2) bool PointInTriangle(glm::vec2& pt, glm::vec2& v1, glm::vec2& v2, glm::vec2& v3) :

A function that receives a point and verticses of a triangle, and returns whether the point is inside the triangle or not.

Main function (also method in Renderer Class):

3) void FillTriangle(glm::vec4& a1, glm::vec4& b1, glm::vec4& c1) :

The function takes verticses of a triangle, and draws it with a random color.

In the main function we find the max_x, min_x and the same for the y, for all the verticses of the triangle, this is to go over the smallest possible space and check for each point whether it is in the triangle or not, if it is then we color it by the putpixel function With random color.

For the random color, for each triangle we define a new color:

glm :: vec3 color1 (rand (), rand (), rand ());

glm :: vec3 color2 (rand (), rand (), rand ());

glm :: vec3 color = color1 / color2;

The division is so that the numbers should be between zero and one.

###### A picture of the output:
![section_1,part_1 image](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment2Report/h2_a_sec1.png)

#### (2):
The work was in Renderer Class, Camera Class, Main Class.

In Camera Class and Main Class the job was just to add a button to the GUI so we could switch from gray scale model to random colored model.

The main work was in Renderer Class, I added three variables - private:

1) float * z_buffer_; :

Indicates the z_buffer where we will save the values of the z coordinate of the points.

2) float min_zbuffer = std :: numeric_limits <float> :: max (); :

Variable to keep the minimum z value, initialize it so as to allow comparison with other values.

3) float max_zbuffer = std :: numeric_limits <float> :: min (); :

Same as (2), but keep the maximum z.

And I also added five methods:

1) void ClearZBuffer (); :

In this function we start all the values in z-buffer to infinity, so that we can identify the points on which we made a change later.

Note: In the CreateBuffers function you set the size of the buffer (as the size of the main window), and then call the function ClearZBuffer.

2) void set_z_buffer_index (int x, int y, float z, const glm :: vec3 & color); :

In this function we update the min_zbuffer and the max_zbuffer and the z-buffer in the coordinates x, y if necessary, and also in case it was necessary to update the z-buffer in the coordinates x, y we will also color this pixel through the putpixel function,
The test whether it is necessary to change or not, is according to the algorithm we learned, i.e. the z-buffer in the coordinates x, y is smaller than our z we will not change, otherwise we will change.

3) float get_triangle_area(int x1, int y1, int x2, int y2, int x3, int y3); :

A function for finding the area of a triangle, which receives the coordinates of the angles of the triangle.

4) void Draw_with_gray (); :

In this function, you go over the z-buffer and color the pixels that were changed after uploading the model.

5) glm :: vec3 Get_GrayColor (float z); :

Use this function within the previous function to know the color in which the pixel should be painted. (Make a weighted average of the z-distance from the maximum z and the minimum z-z to find the appropriate gray level for this pixel).

Inside the function we implemented in part 1 (FillTriangle), and inside the loop that passes and checks if the point inside the triangle, we calculate the area of the triangle itself and the areas of the three triangles formed by the particular point we are examining now, (we will find the areas through the get_triangle_area function), and then find -z of the particular point being tested according to the algorithm we learned:

A1 = get_triangle_area(i,j,b1.x,b1.y,c1.x,c1.y);

A2 = get_triangle_area(i,j,a1.x,a1.y,c1.x,c1.y);

A3 = get_triangle_area(i,j,a1.x,a1.y,b1.x,b1.y);

T_area = A1 + A2 + A3;

newz = (A3 * c1.z) / T_area + (A2 * b1.z) / T_area + (A1 * a1.z) / T_area;

set_z_buffer_index(i,j,newz,color);


And then through the function set_z_buffer_index check if you need to update in z-buffer.

By now we have finished updating in z-buffer and painting in random color, left to paint in gray.

And that's through the Draw_with_gray function.

Call Fill_Triangle function from the Render function after identifying each triangle, and then after completing the transition on all triangles call Draw_with_gray, (add conditions before calling Draw_with_gray, which checks if the user wants the model in gray or colors, i.e. according to the -GUI).

###### A picture of the model in gray:
![h2a_sec2_gray](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment2Report/h2a_sec2_gray.png)

###### A picture of the model in random colors:
![h2a_sec2_colors](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment2Report/h2a_sec2_colors.png)

###### A picture of the model in gray with rotation in y-axis (148):
![h2a_sec2_gray+R](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment2Report/h2a_sec2_gray%2BR.png)

###### A picture of the model in colors with rotation in y-axis (148):
![h2a_sec2_colors+R](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment2Report/h2a_sec2_colors%2BR.png)



