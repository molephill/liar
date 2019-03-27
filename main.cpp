
#include "vld.h" 

#include <Liar3D.h>
#include <core/render/Camera.h>
#include <core/models/Mesh.h>
#include <core/events/EventType.h>
#include <core/models/Model.h>

int main() {

	Liar::Liar3D::Init();

	Liar::Camera* camera3D = new Liar::Camera();
	Liar::Liar3D::stage->AddCamera(camera3D);
	camera3D->SetClearColor(0.2f, 0.3f, 0.3f);
	camera3D->GetViewPort()->SetViewSize(Liar::WINDOW_W, Liar::WINDOW_H);
	camera3D->GetTransform3D().SetPosition(0, 0, -50);
	//camera3D->GetTransform3D().Rotate(3, 0, 0);

	Liar::Liar3D::cameraMoveScript->SetCamera(camera3D);

	/*Liar::Mesh* mesh = new Liar::Mesh(Liar::GeometryType::GEOMETRY_TYPE_BOX);
	Liar::Liar3D::stage->AddChild(mesh);*/

	Liar::Model* model = new Liar::Model();
	model->SetURL("new\\box");
	//model->GetTransform3D().SetScale(0.5f);
	Liar::Liar3D::stage->AddChild(model);

	Liar::Liar3D::Run();

#if defined(POINTLIGHT) || defined(DIRECTIONLIGHT)
	std::cout << "defined" << std::endl;
#else
	std::cout << "ndef" << std::endl;
#endif // DIRECTIONLIGHT || ifdef POINTLIGHT

	return 0;
}