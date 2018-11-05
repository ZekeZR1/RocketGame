#ifndef _GAMEOBJECT_
#define _GAMEOBJECT_
typedef unsigned char GameObjectPrio;
namespace ZekeEngine {
	class GameObject : Noncopyable
	{
	public:
		GameObject() :
			m_priority(0),
			m_isStart(false),
			m_isDead(false),
			m_isNewFromGameObjectManager(false)
		{}
		virtual ~GameObject() {};
	public:
		virtual bool Start() { return true; }
		virtual void Update(){}
		virtual void Render(){}
		virtual void OnDestroy(){}
		GameObjectPrio GetPriority() const {
			return m_priority;
		}
	public:
		virtual void Awake() {}

		//Update
		virtual void PreUpdate(){}
		virtual void PostUpdate(){}
		//Render
		virtual void PreRender(){}
		virtual void PostRender(){}
	public:
		void SetDeadMark()
		{
			m_isDead = true;
		}
		bool IsDead() const
		{
			return m_isDead;
		}		
		virtual bool IsStart() const
		{
			return m_isStart;
		}
		bool IsActive() const
		{
			return m_isActive;
		}
		void SetActiveFlag(bool flag)
		{
			m_isActive = flag;
		}
		void SetTags(unsigned int tags)
		{
			m_tags = tags;
		}
		unsigned int GetTags() const
		{
			return m_tags;
		}

		void PostRenderWrapper()
		{
			if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
				PostRender();
			}
		}
		void RenderWrapper()
		{
			if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
				Render();
			}
		}
		void PreRenderWrapper()
		{
			if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
				PreRender();
			}
		}
		void PostUpdateWrapper()
		{
			if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
				PostUpdate();
			}
		}
		void PreUpdateWrapper()
		{
			if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
				PreUpdate();
			}
		}
		void UpdateWrapper()
		{
			if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
				Update();
			}
		}
		void StartWrapper()
		{
			if (m_isActive && !m_isStart && !m_isDead && !m_isRegistDeadList) {
				if (Start()) {
					m_isStart = true;
				}
			}
		}
		void SetMarkNewFromGameObjectManager()
		{
			m_isNewFromGameObjectManager = true;
		}
		bool IsNewFromGameObjectManager() const
		{
			return m_isNewFromGameObjectManager;
		}
		friend class GameObjectManager;
	protected:
		GameObjectPrio m_priority;
		bool m_isStart;
		bool m_isDead;
		bool m_isRegistDeadList = false;
		bool m_isNewFromGameObjectManager;
		bool m_isRegist = false;
		bool m_isActive = true;
		unsigned int m_tags = 0;
		unsigned int m_nameKey = 0;
	};
}
#endif