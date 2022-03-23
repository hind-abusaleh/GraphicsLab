# Assignment_3
#### (1): 

void Renderer::InitOpenGLRendering():

first we create a buffer to save the mesh info, because from now we will need the buffers to render the model with OPENGL, 
The exture is drawn over two triangles that stretch over the screen, then we load and compile the shaders (vertex and fragment shader), and finely we tells the shader where to look for the vertex position data, and the data dimensions (same for texture coords).

Briefly this function Attend to us all the things that we will need to render in OPENGL, (the buffers, VAO,..) and maps the pixels to the texture coordinates.

#### (3):
Vertex shader:
~~~
#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

// The model/view/projection matrices
uniform mat4 inversmat;
uniform mat4 Tmat;
uniform mat4 proj;
uniform mat4 lookAt_mat;

// These outputs will be available in the fragment shader as inputs
out vec3 orig_fragPos;
out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoords;

void main()
{

            orig_fragPos = vec3(vec4(pos, 1.0f));
			fragPos = vec3( Tmat * vec4(pos, 1.0f));
			fragNormal = mat3( Tmat) * normal ;
			gl_Position = proj * lookAt_mat * inversmat * Tmat * vec4(pos, 1.0f);
	        //fragTexCoords = texCoords;
	
}
~~~

	
    
#### (4):

Fragment shader:
~~~
#version 330 core

struct Material
{
	sampler2D textureMap;
	// You can add more fields here...
	// Such as:
	//		1. diffuse/specular relections constants
	//		2. specular alpha constant
	//		3. Anything else you find relevant
};

// We set this field's properties from the C++ code
//uniform Material material;

// Inputs from vertex shader (after interpolation was applied)
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoords;
in vec3 orig_fragPos;
// The final color of the fragment (pixel)
out vec4 frag_color;

void main()
{
	// Sample the texture-map at the UV coordinates given by 'fragTexCoords'
	//vec3 textureColor = vec3(texture(material.textureMap, fragTexCoords));

	//frag_color = vec4(orig_fragPos,1);
	frag_color = vec4(0,0,1,0);
}

~~~


#### (5):

Render function:
~~~
void Renderer::Render(const std::shared_ptr<Scene>& scene) {

	int cameraCount = scene->GetCameraCount();
	if (cameraCount > 0)
	{
		int modelCount = scene->GetModelCount();
		const Camera& camera = scene->GetActiveCamera();

		for (int currentModelIndex = 0; currentModelIndex < modelCount; currentModelIndex++)
		{
			std::shared_ptr<MeshModel> currentModel = scene->GetModel(currentModelIndex);

			// Activate the 'colorShader' program (vertex and fragment shaders)
			colorShader.use();

			// Set the uniform variables
			colorShader.setUniform("inversmat", camera.get_invTransform_Mat());
			colorShader.setUniform("Tmat", scene->GetActiveModel()->get_Transform_Mat());
			colorShader.setUniform("proj", camera.GetProjectionTransformation());
			colorShader.setUniform("lookAt_mat", camera.get_lookAt_mat());
			//colorShader.setUniform("material.textureMap", 0);
			

			// Set 'texture1' as the active texture at slot #0
			//texture1.bind(0);

			// Drag our model's faces (triangles) in fill mode
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBindVertexArray(currentModel->GetVAO());
			glDrawArrays(GL_TRIANGLES, 0, currentModel->GetModelVertices().size());
			glBindVertexArray(0);

			// Unset 'texture1' as the active texture at slot #0
			//texture1.unbind(0);

			colorShader.setUniform("color", glm::vec3(0, 0, 0));

			
		}
	}
}
~~~

###### the mesh:
![5](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment3Report/5/5.png)


#### (6):
Adding the light and the phong shading:

for the light shape I saved the vertices like we have done before in the mesh model (buffers) and then i access it by the   ShaderProgram lightShader;   that I added in the rendrer class.

###### car with point light:
![car100_pointlight](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment3Report/6/car100_pointlight.png)

###### car with parallel light:
![car100_paralight](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment3Report/6/car100_paralight.png)


###### car with parallel and point light:
![car100_point_para](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment3Report/6/car100_point_para.png)


###### car with point light (+ light transformation):
![car100_pointlight_trans](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment3Report/6/car100_pointlight_trans.png)


###### car with point light (+ car transformation):
![car100_trans](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment3Report/6/car100_trans.png)

###### More examples:
###### bunny with point and parallel light:
![bunny_point_paralight](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment3Report/6/bunny_point_paralight.png)


###### bunny with point and parallel light (+ bunny transformation):
![bunny_point_paralight_trans](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment3Report/6/bunny_point_paralight_trans.png)


###### tow point lights:
![2_pointlight](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment3Report/6/2_pointlight.png)


###### tow point lights + parallel light:
![2_point_1paralight](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment3Report/6/2_point_1paralight.png)



#### (7):
I implemented the plane mapping, here some pictures to the results:


###### beethoven:
![beet_texture](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment3Report/7/beet_texture.png)


###### beethoven transformation:
![beet_texture_trans](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment3Report/7/beet_texture_trans.png)


###### crate transformation:
![crate_texture](https://github.com/HaifaGraphicsCourses/computergraphics2021-hind/blob/master/Assignment3Report/7/crate_texture.png)


