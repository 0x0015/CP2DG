#include "GameObject.hpp"
#include "../audio.h"
#include <vector>

class MusicObject : public GameObject{//for use of keeping track of time sig, beat timings, etc... for aligning with music
public:
	std::string audioPath;
	Audio* audio;
	float sampleToSec;
	float bpm;
	std::vector<std::pair<float, float>> tempoChanges;
	std::vector<std::pair<float, float>> timeSignChanges;
	std::vector<std::pair<float, float>> beatSyncs;
	float timeSinceLastBeat;
	bool onBeat;
	bool onDownBeat;
	float lastTimeCheck;
	float lastTempoCheckTime;
	int LastBeat;
	float currentBeat;
	int LastBeatInMeasure;
	float currentBeatInMeasure;
	float timeSign;
	float lastTimeSignCheckTime;
	bool audioStarted = false;
	void Initialize();
	void Load();
	void Draw();
	void Update();
	void CheckTempoChange();
	void CheckTSChange();
	void CheckBeatSync();
	//blueprint
	static inline std::unordered_map<std::string, std::string> Blueprint = {
		{"position", "std::pair<float,float>"},
		{"SpawnTime", "int"},
		{"depth", "float"},
		{"name", "std::string"},
		{"audioPath", "std::string"}
	};
	std::unordered_map<std::string, void*> Create_Bp = {
		{"position", &position},
		{"SpawnTime", &SpawnTime},
		{"depth", &depth},
		{"name", &name},
		{"audioPath", &audioPath}
	};

};
