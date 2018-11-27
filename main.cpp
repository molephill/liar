
#include <Liar3D.h>
#include <core/display/Scene.h>
#include <core/render/Camera.h>
#include <core/models/BoxMesh.h>

int main() {

	Liar::Liar3D::Init();

	Liar::Scene* scene = new Liar::Scene();
	Liar::Liar3D::stage->AddChild(scene);

	Liar::Camera* camera3D = new Liar::Camera();
	Liar::Liar3D::stage->AddCamera(camera3D);
	camera3D->SetClearColor(0.2f, 0.3f, 0.3f);
	camera3D->GetViewPort()->SetViewSize(Liar::WINDOW_W, Liar::WINDOW_W);

	Liar::Liar3D::Run();

	return 0;
}