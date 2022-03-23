# Assignment_2, part_2
#### (1): 
The work was in - Light Class (new class), Renderer Class, Main and Scene.
First in Light Class that I added, there is 9 float parameters for the colors parts (ambient, diffuse, specular), and an int parameter for alpha in Phong light case,
in addition to an int parameter-a unique number for each light, to in order to access a specific light later. As well, I added a flag to figure out if the type is point or parallel, and tow vectors one for the direction(in parallel case), and the second is for the position, and finally an-11 matrices to implement the transformations in point light case(same matrices that I added formerly in the first assignment to implement the transformations for the model). 
For each private member, I added a setters and getters functions, each according to its work.  

Second, in Renderer Class, I added a function to draw the light shape, according to its position, and I called it in the Render function inside of for loop that goes over the lights (the light are added to an lights vector in the Scene Class).In addition to the functions to calculate the parts of colors (material + light),

(1): glm::vec3 Ambient_color(glm::vec3& light, glm::vec3& model);
	
(2): glm::vec3 Diffuse_Color(glm::vec3 n, glm::vec3& i, glm::vec3& color, glm::vec3& light);
	
(3): glm::vec3 Specular_Color(glm::vec3 n, glm::vec3& i, glm::vec3& v, glm::vec3& color, glm::vec3& light, int alpha);
	    
the implementation for each function is according to the lecture lighting and shading.

Third, in Scene Class,as I mentioned before, I added a lights vector and a few functions to access the lights and make changes on them. 

Lastly, in the Main I added a new window called a Light Window, in these window I added buttons and stuff to add lights and control its qualities.



#### (2):
For these section I added a 9 float parameters for the colors parts (ambient, diffuse, specular) in the MeshModel Class, similarly to the previous section.
In addition to some changes in GUI to allow user to control the model material. 



#### (3):
For these section I added some functions to the Renderer Class:

(1): void FillTriangle_Gouraud(const glm::vec3& a1, const glm::vec3& b1, const glm::vec3& c1, glm::vec3& color1, glm::vec3& color2, glm::vec3& color3);

(2): void FillTriangle_Flat(const glm::vec3& a1, const glm::vec3& b1, const glm::vec3& c1, glm::vec3 color);
	
(3): void FillTriangle_Phong(const glm::vec3& a1, const glm::vec3& b1, const glm::vec3& c1, glm::vec3 nor1, glm::vec3 nor2, glm::vec3 nor3, const Scene& scene, Light& light, glm::vec3 position, int flag);
	
plus some more help functions,

In function (2), I implement the flat shading, similarly to the past fill_triangle, put in this function amend the Color Buffer according to the color that we calculate according to the total returns of the three functions that I added previously(ambient_color, diffuse_color and specular_color). these function works per face (all the points in the same face have the same color).

In function (1), this function works according to the influence degree of the vertices colors on the point in the face (similarly to the z_buffer in the previous part of this assignment), so first we calculate the direction of the light (according to its type), and then we calculate the vertices colors according to the functions (ambient_color, diffuse_color and specular_color), and finally we update the color buffer according to the color we have after checking the effect of the vertices.   

In function (3), we want to apply the illumination equation for each interior point or pixel with its own (interpolated) normal, so we find the z_buffer vector of the normals for the specific point:

A1 = get_triangle_area(x, y, b1.x, b1.y, c1.x, c1.y);

	A2 = get_triangle_area(x, y, a1.x, a1.y, c1.x, c1.y);
	A3 = get_triangle_area(x, y, a1.x, a1.y, b1.x, b1.y);
	T_area = A1 + A2 + A3;
	newz = (A3 * norm3.z) / T_area + (A2 * norm2.z) / T_area + (A1 * norm1.z) / T_area;
	newy = (A3 * norm3.y) / T_area + (A2 * norm2.y) / T_area + (A1 * norm1.y) / T_area;
	newx = (A3 * norm3.x) / T_area + (A2 * norm2.x) / T_area + (A1 * norm1.x) / T_area;
	glm::vec3 n = glm::vec3(newx, newy, newz);
    
and then we find the color according to this vector (n) and the I (light direction),
and update the  color buffer.

	
    
#### (4):

In the images bellow, I set the model material to be: (243, 250, 5) for ambient. (246, 254, 4) for diffuse. (2334, 249, 2) for specular.

And, I set the light color to be: (245, 101, 101) for ambient. (216, 102, 102) for diffuse. (146, 55, 55) for specular. 

###### Flat_point (with light translation in X axis(0.05) ):
![flat_point](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment2Report/part2_images/flat_point.png)

###### Flat_parallel:
![flat_parallel](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment2Report/part2_images/flat_parallel.png)

###### Gouraud_point (with light translation in X axis(0.01) and light rotation in X axis(74)):
![gouraud_point](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment2Report/part2_images/gouraud_point.png)

###### Gouraud_parallel:
![gouraud_parallel](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment2Report/part2_images/gouraud_parallel.png)

###### Phong_point (with light translation in X axis(0.01) and alpha=5):
![phong_point](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment2Report/part2_images/phong_point.png)

###### Phong_parallel:
![phong_parallel](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment2Report/part2_images/phong_parallel.png)

And the two images bellow are clarify the difference between the Phong and the Gouraud shading:
light color: (241, 28, 28) for ambient. (221, 47, 47) for diffuse. (239, 29, 29) for specular. 
in addition to the light rotation: in X axis(77) and in Z axis(105). 

###### Gouraud_point_shading:
![gouraud_point_shading](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment2Report/part2_images/d_gouraud.png)

###### Phong_point_shading:
![phong_point_shading](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment2Report/part2_images/d_phong.png)



#### (5):

For this section I implement a Fog effect function in Renderer Class, this function implements the Fog linear equation (according to the formula in the lecture).

The following two pictures show the difference and how's that with Fog (the outermost points are darker).

###### without_fog:
![without_fog](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment2Report/part2_images/without_fog.png)

###### with_fog:
![with_fog](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment2Report/part2_images/with_fog.png)


