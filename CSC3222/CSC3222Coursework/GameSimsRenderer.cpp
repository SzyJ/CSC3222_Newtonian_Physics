#include "GameSimsRenderer.h"
#include "../../Common/Vector2.h"
#include "../../Common/Vector3.h"
#include "../../Common/Matrix4.h"

#include "SimObject.h"
using namespace NCL;
using namespace Rendering;
using namespace CSC3222;

GameSimsRenderer::GameSimsRenderer() : OGLRenderer(*Window::GetWindow())	{
	spriteShader = new OGLShader("GameSimsSpriteVert.glsl", "GameSimsSpriteFrag.glsl");

	spriteMesh = new OGLMesh();

	spriteMesh->SetVertexPositions({ Vector3(0, 0, 0), Vector3(0, 1, 0), Vector3(1, 0, 0) , Vector3(1, 1, 0) });
	spriteMesh->SetVertexTextureCoords({ Vector2(0,0),  Vector2(0,1) , Vector2(1,0) , Vector2(1,1) });

	spriteMesh->SetPrimitiveType(NCL::GeometryPrimitive::TriangleStrip);

	spriteMesh->UploadToGPU();

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

GameSimsRenderer::~GameSimsRenderer()	{
	delete spriteShader;
	delete spriteMesh;
}

void GameSimsRenderer::SetScreenProperties(int tileSize, int numTilesX, int numTilesY) {
	this->tileSize	= tileSize;
	this->numTilesX = numTilesX;
	this->numTilesY = numTilesY;
}

void GameSimsRenderer::AddSimObject(const SimObject* s) const {

}

void GameSimsRenderer::RemoveSimObject(const SimObject* s) {

}

void GameSimsRenderer::Update(float dt) {
	texAreas.clear();
}

void GameSimsRenderer::RenderFrame()	{
	//sort tex areas;

	BindShader(spriteShader);
	BindMesh(spriteMesh);

	GLuint screenSize	= glGetUniformLocation(spriteShader->GetProgramID(), "screenSize");
	GLuint spritePos	= glGetUniformLocation(spriteShader->GetProgramID(), "spritePos");
	GLuint spriteSize	= glGetUniformLocation(spriteShader->GetProgramID(), "spriteSize");

	GLuint texPos	= glGetUniformLocation(spriteShader->GetProgramID(), "texPos");
	GLuint texSize	= glGetUniformLocation(spriteShader->GetProgramID(), "texSize");

	GLuint invertX = glGetUniformLocation(spriteShader->GetProgramID(), "invertX");

	GLuint projMatrix = glGetUniformLocation(spriteShader->GetProgramID(), "projMatrix");


	Matrix4 ortho = Matrix4::Orthographic(-1, 1, tileSize * numTilesX, 0, 0, tileSize * numTilesY); //each sprite is 16 pixels, times how many sprites we want

	glUniformMatrix4fv(projMatrix, 1, false, ortho.values);

	glUniform2f(screenSize, tileSize * numTilesX, tileSize * numTilesY); //

	glDisable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (auto &tex : texAreas) {
		BindTextureToShader(tex.texture, "spriteTex", 0);

		glUniform2f(spritePos, tex.screenPos.x, tex.screenPos.y); //
		glUniform2f(spriteSize, tex.size.x, tex.size.y); //

		glUniform2f(texPos, tex.start.x, tex.start.y); //
		glUniform2f(texSize, tex.size.x, tex.size.y); //

		glUniform1i(invertX, tex.flipX);

		DrawBoundMesh(0, 1);
	}	
}

void GameSimsRenderer::DrawTextureArea(OGLTexture* texture, Vector2 start, Vector2 size, Vector2 screenPos, bool invertX) {
	TextureArea t;
	t.texture	= texture;
	t.screenPos = screenPos;
	t.start		= start;
	t.size		= size;
	t.flipX		= invertX;

	texAreas.emplace_back(t);
}