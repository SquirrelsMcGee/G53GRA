#include "ModelObject.h"

ModelObject::ModelObject(MyScene *scene, int id, std::string objectName, ColorRGB *color, std::string fileName, int winding)
	: WorldObject(scene, id, objectName, color)
{
	/* By default, the *.obj and *.bmp files have the same filename 
	** This is so models and their textures are matched
	** _texId is a publicly accessibly variable so you can change the texture
	** at a later point in time
	** *.obj files should be placed in the Model folder
	** *.bmp files should be placed in the Texture folder
	*/
	_obj_path = "../Model/" + fileName + ".obj";
	_tex_path = "../Texture/" + fileName + ".bmp";

	/* Create the ObjectFileReader and load the *.obj file */
	objectFileReader = new ObjectFileReader(_obj_path);
	objectFileReader->Load();

	/* Get the vectors from the file reader */
	faces = objectFileReader->faces;
	vertices = objectFileReader->vertices;
	textureCoordinates = objectFileReader->textureCoordinates;
	normals = objectFileReader->normals;
	faceMaterials = objectFileReader->faceMaterials;

	/* Set the texture id */
	_texId = scene->GetTexture(_tex_path);
}


ModelObject::~ModelObject()
{
}

void ModelObject::Display() {
	/* This function is used to initialise rendering to the screen */

	if (!doRender) return;

	glPushMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _texId);

	/* Enable all the lights that are currently registered in MyScene */
	for (size_t i = 0; i < scene->lights->size(); ++i) {
		glEnable(GL_LIGHT0 + (int)i);
	}

	/* Translate origin of the model, scale and rotate from given values */
	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f); // angle ry about (0,1,0)
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f); // angle rz about (0,0,1)
	glRotatef(rotation[0], 1.0f, 0.0f, 0.0f); // angle rx about (1,0,0)

	/* Update ambient and diffuse light attributes from given value */
	mat_ambient[0] = light_color->x;
	mat_ambient[1] = light_color->y;
	mat_ambient[2] = light_color->z;
	mat_diffuse[0] = light_color->x;
	mat_diffuse[1] = light_color->y;
	mat_diffuse[2] = light_color->z;
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	/* Begin rendering the model */
	Render();

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glPopMatrix();
}

void ModelObject::Render() {
	/* This function iterates over every stored face that was loaded
	** It then determines if the face has 3 or 4 vertices within it
	** and begins rendering a triangle or a quad depending on the result
	*/
	for (size_t faceId = 0; faceId < faces.size(); faceId++) {

		Face * face = faces[faceId];
		if (face->faceData->size() == 3) {
			glBegin(GL_TRIANGLES);
		}
		else {
			glBegin(GL_QUADS);
		}

		/* Set the colour and begin rendering the current face */
		glColor3f(color->x, color->y, color->z);
		RenderFace(face);
		glEnd();
		glClearColor(0, 0, 0, 1.0);
	}
	
}

void ModelObject::RenderFace(Face * face) {
	/* This function renders a Face 
	** First I get the current face data, then render the normal, 
	** texture coordinate, and vertex in that order
	*/

	std::vector<Vertex*> *faceData = face->faceData;

	for (size_t vertexId = 0; vertexId < faceData->size(); ++vertexId) {
		Vertex * data = faceData->at(vertexId);

		int normalIndex = (int)data->z; // Index position of the normal within the normals list
		if (normalIndex > -1 && normalIndex < (int) normals.size())
			RenderNormal(normalIndex);
		
		int materialIndex = (int)data->y; // Index position of the texture coordinate within the materials list
		if (materialIndex > -1 && materialIndex < (int) textureCoordinates.size())
			RenderMaterial(materialIndex);

		int vertexIndex = (int)data->x; // Index position of the vertex within the vertices list
		if (vertexIndex > -1 && vertexIndex < (int)vertices.size())
			RenderVertex(vertexIndex);
		
	}
}

void ModelObject::RenderVertex(int vertexIndex) {
	/* Get the vertex at the index given and render it */
	Vertex * vertexCoordinates = vertices[vertexIndex];
	glVertex3f(vertexCoordinates->x, vertexCoordinates->y, vertexCoordinates->z);
}

void ModelObject::RenderNormal(int normalIndex) {
	/* Get the normal at the index given and render it */
	Vertex * normal = normals[normalIndex];
	glNormal3f(normal->x, normal->y, normal->z);
}

void ModelObject::RenderMaterial(int texCoordIndex) {
	/* Get the texture coordinates at the index given and render it */
	float * textureCoordinate = textureCoordinates[texCoordIndex];
	glTexCoord2f(textureCoordinate[0], textureCoordinate[1]);
}