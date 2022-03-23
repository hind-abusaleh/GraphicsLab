# Assignment_1, part_3
#### (1): 
###### A picture of the output:
![section_1,part_3 image](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment1Report/section_1%2Cpart_3.png)

#### (2):
T1= translate (300x300)(300 in X axis, and 300 in Y axis)
    scaling (2x0.5)(2 in X axis, and 0.5 in Y axis).
T2= rotation in Y axis(-70) 
    translate (300x300)(300 in X axis, and 300 in Y axis)
###### A picture of the output(T1 in world and T2 in local):
![W_L_sec2_part3 image](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment1Report/W_L_sec2_part3.png)
###### A picture of the output(T1 in local and T2 in world):
![L_W_sec2_part3 image](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment1Report/L_W_sec2_part3.png)



#### (3):
I added a GUI button to each of the following:
bounding box, face normals, vertex normals
And I kept a flag in MeshModel class to detect if any of the actions occur
So if we clicked on the BOUNDING BOX for example, the flag is updated to be 1, and then we check in MAIN for each of the FLAGs if they are on.
In the case of bounding box: In previous parts we did, we used the maximum and minimum of the points of the model we loaded, we found these points in Utils class so I used them by passing them to MeshModel's constructor, and then I did in MeshModel a functions that returns a vector representing each From the faces of the bounding box, the vector was calculated as follows:- First we create a vector from the points that represent the face, (i.e. the points that make the face), and then multiply it by the transformation matrix.
So in Render it remains to check the flag and then call the functions and draw through a drawline function.

In the case of faceNormals and vertexNormals: I did exactly as described in the lecture, went through all the faces, found the vectors and did them (for subtracting from each other, as in the lecture) cross and then normalize, I found the center of the face and then drew,
Same with vertexNormals.

Important Note: In the next section when adding the camera I update the vectors by multiplying them by the inverse of the transformation matrix of the camera (and also the projection matrix and the lookat matrix)

###### A picture of the bounding box:

![bounding_box Image](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment1Report/section3_part3_box.png)

###### A picture of the faceNormals:

![face_normals Image](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment1Report/section3_part3_faceNormals.png)

###### A picture of the vertexNormals:

![vertex_normals Image](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment1Report/section3_part3_verNormals.png)


#### (4):
First: I have added the following methods to the Camera class
1)  void set_orth (float x);
2)  void set_perspective (float x);
3)  void set_orth_flag (int flag);
4)  int get_orth_flag () const;

(1) Use this method when clicking on orthographic projection, the method gets the ortho_width that the user wants, the function updates the parameters (the parameters of the camera, i.e. the width, height, aspect ratio, right, left, button, top) and calls to glm::ortho with the updated parameters, and the result is saved in the projection_transformation matrix.

(2) Use this method when clicking on perspective projection, the method gets the fovy the user wants, the function updates the fovy parameter of the camera and calls glm :: perspective with the updated parameters, and the result is saved in projection_transformation matrix.

(3) Use this method every time you switch from orthographic projection, to perspective projection, or vice versa. This method gets 1 if we are in orthographic projection, and zero otherwise, and it updates the flag (which we added to camera privet to separate the modes).

(4) The method returns the flag I talked about earlier, in this method we use Render because we need to separate the way to draw in orthographic projection, and perspective projection, (because in perspective projection, we need to divide the vetex vectors of each face in their W, to keep of transition from homogeneous coordinates).

Second: I have also added the following methods
void set_translation_w (float x, float y, float z);
void set_rotation_w (float a, float x, float y, float z);
void set_translation_L (float x, float y, float z);
void set_rotation_L (float a, float x, float y, float z);
const glm :: mat4x4 get_invTransform_Mat () const;
void set_invTransform_Mat (int flag);

The first four methods are like the methods that support translation, rotation in the MeshModel class that we implemented in previous sections.

The fifth and sixth methods are one to update the camera's transformation matrix and make it an inverse fabric that we can use (as we learned in the lecture), and the other is to take the updated matrix and use it in a render when you want to draw.

Third: I implemented the Camera GUI.

Fourth: I added the LookAT parameters to the GUI, (eye, at, up) so that the user can change them.
And then I updated the method that is in the camera:
void SetCameraLookAt (const glm :: vec3 & eye, const glm :: vec3 & at, const glm :: vec3 & up);
This method takes the vectors of the parameters (eye, at, up) and then runs the function glm::lookAt on them, the result is kept in the privet variable and we add a get method to the result (matrix), so that we can touch it when we need to (in render).

Fifth: I updated the Render function to appropriate the drawing with the actions done on the camera and not just on the model,
I multiplied by the inverse of the transformation matrix of the camera and the lookAt matrix and the projection matrix in addition to the scale_translate matrix to so we can see the model.
the order of the matrices multiplication: a1 = scale_translate * proj * lookAt_mat * inversmat * Transformation_mat * glm::vec4(scene.GetActiveModel().GetVer(I1), 1);

###### orthographic projection:
![orth_case Image](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment1Report/sec4_part3_orth.png)

###### perspective projection:
![per_case Image](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment1Report/sec4_part3_per.png)



#### (5):
###### A picture after changing the fovy:

![fovy Image](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment1Report/sec5_part3_fovy.png)

###### A picture after translating in z's axis:

![zTranslate Image](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment1Report/sec5_part3_ztrans.png)


#### (6):
###### A picture after translate in the world and rotate in the camera:

![w_l Image](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment1Report/sec6_w_l.png)

###### A picture after translate in the camera and rotate in the world:

![l_w Image](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment1Report/sec6_l_w.png)


#### (7):
###### A picture with eye vector (11,11,11):

![sec7 Image](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment1Report/sec7_part3.png)

#### (9):
###### A picture before minimizing the window :

![sec9_1 Image](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment1Report/sec9_part3_1.png)

###### A picture after minimizing the window :

![sec9_2 Image](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment1Report/sec9_part3_2.png)

#### (10):
###### A picture of the GUI :

![GUI Image](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment1Report/sec10_part3_GUI.png)
