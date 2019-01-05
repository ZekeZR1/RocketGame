/*!
* @brief	コライダー。
*/

#pragma once
class btCollisionShape;

namespace ZekeEngine {
	/*!
	* @brief	コライダーのインターフェースクラス。
	*/
	class ICollider {
	public:
		virtual btCollisionShape* GetBody() const = 0;
	};
}