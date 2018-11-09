#pragma once

#include "GameObject.h"

namespace ZekeEngine {
	class CGameObjectManager : Noncopyable
	{
	public:
		CGameObjectManager() :
			m_gameObjectPriorityMax(0) {
		}
		~CGameObjectManager() {};
	public:
		static unsigned int MakeGameObjectNameKey(const char* objectName)
		{
			static const unsigned int defaultNameKey = CUtil::MakeHash("Undefined");
			unsigned int hash;
			if (objectName == nullptr) {
				hash = defaultNameKey;
			}
			else {
				hash = CUtil::MakeHash(objectName);
			}
			return hash;
		}
	public:
		static CGameObjectManager& Instance()
		{
			static CGameObjectManager instance;
			return instance;
		}

		void Execute();
		void Init(int gameObjectPrioMax);
		void AddGameObject(GameObjectPrio prio, GameObject* go, const char* objectName = nullptr)
		{
			(void)objectName;
			if (!go->m_isRegist) {
				go->Awake();
				unsigned int hash = MakeGameObjectNameKey(objectName);
				m_gameObjectListArray.at(prio).push_back(go);
				go->m_isRegist = true;
				go->m_priority = prio;
				go->m_isStart = false;
				go->m_nameKey = hash;
				if (go->m_isDead) {
					go->m_isDead = false;
				}

			}
		}

		void Pause() {
			m_isPause = true;
		}

		void PauseRelease() {
			m_isPause = false;
		}

		template<class T, class... TArgs>
		T* NewGameObject(GameObjectPrio prio, const char* objectName, TArgs... ctorArgs)
		{
			(void*)objectName;
			assert(prio <= m_gameObjectPriorityMax && "ゲームオブジェクトの優先度の最大数が大きすぎます。");
			T* newObject = new T(ctorArgs...);
			newObject->Awake();
			newObject->SetMarkNewFromGameObjectManager();
			m_gameObjectListArray.at(prio).push_back(newObject);
			unsigned int hash = MakeGameObjectNameKey(objectName);
			newObject->m_isRegist = true;
			newObject->m_priority = prio;
			newObject->m_nameKey = hash;
			return newObject;
		}


		void DeleteGameObject(GameObject* gameObject)
		{
			if (gameObject != nullptr
				&& gameObject->m_isRegist
				) {
				gameObject->SetDeadMark();
				gameObject->OnDestroy();
				gameObject->m_isRegist = false;
				gameObject->m_isRegistDeadList = true;

				m_deleteObjectArray[m_currentDeleteObjectBufferNo].at(gameObject->GetPriority()).push_back(gameObject);
				gameObject = nullptr;
			}
		}

		template<class T>
		T* FindGameObject(const char* objectName)
		{
			unsigned int nameKey = CUtil::MakeHash(objectName);
			for (auto goList : m_gameObjectListArray) {
				for (auto go : goList) {
					if (go->m_nameKey == nameKey) {
						T* p = dynamic_cast<T*>(go);
						if (p == nullptr) {
							char message[256];
							strcpy_s(message, " 型変換に失敗しました。テンプレート引数を確認してください\n");
							OutputDebugStringA(message);
						}
						return p;
					}
				}
			}
			return nullptr;
		}
		template<class T>
		void FindGameObjects(const char* objectName, std::function<bool(T* go)> func)
		{
			unsigned int nameKey = CUtil::MakeHash(objectName);
			for (auto goList : m_gameObjectListArray) {
				for (auto go : goList) {
					if (go->m_nameKey == nameKey) {
						T* p = dynamic_cast<T*>(go);
						if (func(p) == false) {
							return;
						}
					}
				}
			}
		}

		void FindGameObjectsWithTag(unsigned int tags, std::function<void(GameObject* go)>func)
		{
			for (auto& goList : m_gameObjectListArray) {
				for (auto& go : goList) {
					unsigned int goTags = go->GetTags();
					if ((goTags & tags) != 0) {
						func(go);
					}
				}
			}

		}
	private:
		void ExecuteDeleteGameObjects();
		void UpdateSceneGraph();
	private:
		CTransform m_transform;
		typedef std::list<GameObject*>	GameObjectList;
		std::vector<GameObjectList>	m_gameObjectListArray;				
		std::vector<GameObjectList>	m_deleteObjectArray[2];				
		std::list<CTransform*>		m_childrenOfRootTransformList;			
		GameObjectPrio				m_gameObjectPriorityMax;				
		int m_currentDeleteObjectBufferNo = 0;								
		static const unsigned char 			GAME_OBJECT_PRIO_MAX = 255;
		bool m_isPause = false;
	};

	template<class T, class... TArgs>
	static inline T* NewGO(int priority, const char* objectName, TArgs... ctorArgs)
	{
		return CGameObjectManager().NewGameObject<T>((GameObjectPrio)priority, objectName, ctorArgs...);
	}


	static inline void DeleteGO(GameObject* go)
	{
		CGameObjectManager().DeleteGameObject(go);
	}

	static inline void AddGO(int priority, GameObject* go, const char* objectName = nullptr)
	{
		CGameObjectManager().AddGameObject(static_cast<GameObjectPrio>(priority), go, objectName);
	}

	static inline 	void FindGameObjectsWithTag(unsigned int tags, std::function<void(GameObject* go)>func)
	{
		CGameObjectManager().FindGameObjectsWithTag(tags, func);
	}

	template<class T>
	static inline T* FindGO(const char* objectName)
	{
		return CGameObjectManager().FindGameObject<T>(objectName);
	}

	template<class T>
	static inline void QueryGOs(const char* objectName, std::function<bool(T* go)> func)
	{
		return CGameObjectManager().FindGameObjects<T>(objectName, func);
	}

	static inline CGameObjectManager& GameObjectManager() {
		return CGameObjectManager::Instance();
	}
}