#include "GameObjects/MusicObject.hpp"
#include "Main.hpp"
#include "AssetLoader.hpp"
#include "audio.h"
#include "InputHandler.hpp"
#include "JsonLoader/json.hpp"
#include "../SimpleCppTextFileHandler/file.hpp"

using json = nlohmann::json;

void MusicObject::Initialize(){
	mainWindow->Assets->AudioRequiredPath(audioPath);
	sampleToSec = 1.0/(44100.0*2.0*2.0);//one two because of stereo, don't know where the other one is coming from
	LastBeat = 0;
	currentBeat = 0;
	currentBeatInMeasure = 1;
	LastBeatInMeasure = 1;
}

void MusicObject::Load(){
	audio = mainWindow->Assets->Audios[audioPath];
	auto j = json::parse(readFile("Content/Audio/" + audioPath + ".json"));
	for(int i=0;i<j.size();i++){
		if((j[i].contains("time") && j[i].contains("tempo"))){
			float tempTime = j[i]["time"].get<float>();
			float tempTempo = j[i]["tempo"].get<float>();
			std::pair<float, float> tempoChange = std::pair<float, float>(tempTime, tempTempo);
			tempoChanges.push_back(tempoChange);
		}else if(j[i].contains("time") && j[i].contains("time sign")){
			float tempTime = j[i]["time"].get<float>();
			float tempTS = j[i]["time sign"].get<float>();
			std::pair<float, float> signChange = std::pair<float, float>(tempTime, tempTS);
			timeSignChanges.push_back(signChange);
		}else if(j[i].contains("time") && j[i].contains("beat sync")){
			float tempTime = j[i]["time"].get<float>();
			float tempSync = j[i]["beat sync"].get<float>();
			std::pair<float, float> syncChange = std::pair<float, float>(tempTime, tempSync);
			beatSyncs.push_back(syncChange);
		}
	}
	std::sort(tempoChanges.begin(), tempoChanges.end(), [](const std::pair<float, float> obj1, const std::pair<float, float> obj2){
			return(obj1.first > obj2.first);
			});
	std::sort(timeSignChanges.begin(), timeSignChanges.end(), [](const std::pair<float, float> obj1, const std::pair<float, float> obj2){
			return(obj1.first > obj2.first);
			});
	std::sort(beatSyncs.begin(), beatSyncs.end(), [](const std::pair<float, float> obj1, const std::pair<float, float> obj2){
			return(obj1.first > obj2.first);
			});
}

void MusicObject::CheckTempoChange(){
	if(tempoChanges.size() > 0){
		if(tempoChanges.back().first <= (float)(audioTime-audio->startTime)*sampleToSec){
			if(mainWindow->debug)
				std::cout<<"Tempo change from "<<bpm<<" at "<<lastTempoCheckTime<<" to "<<tempoChanges.back().second<<" at "<<tempoChanges.back().first<<std::endl;
			bpm = tempoChanges.back().second;
			lastTempoCheckTime = tempoChanges.back().first;
			tempoChanges.pop_back();
			CheckTempoChange();
		}
	}
}

void MusicObject::CheckTSChange(){
	if(timeSignChanges.size() > 0){
		if(timeSignChanges.back().first <= (float)(audioTime-audio->startTime)*sampleToSec){
			if(mainWindow->debug)
				std::cout<<"Time sign change from "<<timeSign<<" at "<<lastTimeSignCheckTime<<" to "<<timeSignChanges.back().second<<" at "<<timeSignChanges.back().first<<std::endl;
			timeSign = timeSignChanges.back().second;
			lastTimeSignCheckTime = timeSignChanges.back().first;
			timeSignChanges.pop_back();
			CheckTSChange();
		}
	}
}

void MusicObject::CheckBeatSync(){
	if(beatSyncs.size() > 0){
		if(beatSyncs.back().first <= (float)(audioTime-audio->startTime)*sampleToSec){
			if(mainWindow->debug)
				std::cout<<"Tempo change from at"<<beatSyncs.back().first<<" on beat "<<beatSyncs.back().second<<std::endl;
			timeSinceLastBeat = 0;
			onBeat = true;
			LastBeat = (int)beatSyncs.back().second;
			currentBeat = beatSyncs.back().second;
			lastTempoCheckTime = beatSyncs.back().first;
			beatSyncs.pop_back();
			CheckBeatSync();
		}
	}
}

void MusicObject::Update(){
	//if(mainWindow->Input->isKeyPressed(SDL_SCANCODE_SPACE)){
	if(!audioStarted){
		playSoundFromMemory(audio, SDL_MIX_MAXVOLUME);
		audioStarted = true;
	}
	CheckTempoChange();
	CheckTSChange();
	CheckBeatSync();
	
	float currentTime = ((float)(audioTime-audio->startTime)*sampleToSec);

	timeSinceLastBeat += currentTime-lastTimeCheck;
	//std::cout<<"time Since last beat:"<<timeSinceLastBeat<<" bpm(seconds):"<<1/(bpm/60.0)<<std::endl;
	if(timeSinceLastBeat >= 1/(bpm/60.0)){
		timeSinceLastBeat -= 1/(bpm/60.0);//can't just set to 0 because we don't know how procise this timing is
		if(mainWindow->debug)
			std::cout<<"beat at time "<<currentTime<<std::endl;
		onBeat = true;
		LastBeat++;
		LastBeatInMeasure++;
		if(LastBeatInMeasure > 1/timeSign){
			LastBeatInMeasure = 1;
			onDownBeat = true;
		}

	}else{
		onBeat = false;
		onDownBeat = false;
	}
	currentBeat += (currentTime-lastTimeCheck) * (bpm/60.0);//it works, don't question it.
	currentBeatInMeasure = std::fmod(currentBeat,(float)(1.0/timeSign))+1;
	//std::cout<<currentBeatInMeasure<<" "<<LastBeatInMeasure<<std::endl;
	lastTimeCheck = (float)(audioTime-audio->startTime)*sampleToSec;
	//std::cout<<(float)(audioTime-audio->startTime)*sampleToSec<<std::endl;
	//}
	//std::cout<<audio->startTime<<std::endl;
	//std::cout<<audioTime<<std::endl;
}

void MusicObject::Draw(){

}
