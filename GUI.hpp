#include "GameObjects/RenderObject.hpp"


class GUI : public RenderObject{
private:
	bool loaded = false;
	bool initialized = false;
public:
	void Initialize();
	void Load();
	void Draw();
	void Update();
	void addElement(std::shared_ptr<GameObject> obj);
	~GUI();
};
