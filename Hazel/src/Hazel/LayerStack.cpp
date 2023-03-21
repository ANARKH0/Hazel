#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel {

	LayerStack::LayerStack() {

		m_LayerInsert = m_Layers.begin();
	}
 
	LayerStack::~LayerStack() {

		for (Layer* layer : m_Layers) { // 在应用生命周期结束时对层进行析构，在层更新时只弹出栈，但不销毁（析构）
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer) {

		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer); // 构造 layerInsert 对象的实列化, 在插入前的m_LayerInsert索引处
		layer->OnAttach();

	}

	void LayerStack::PushOverlay(Layer* overlay) {

		m_Layers.emplace_back(overlay);   // 覆盖层在栈顶构造,vector数组末尾
		overlay->OnAttach();

	}

	void LayerStack::PopLayer(Layer* layer) {

		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer); // it 是 vector<Layer*>::iterator
		if (it != m_Layers.end()) {

			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsert--; // vector<Layer*>::iterator type 支持 -- 操作

		}
	}

	void LayerStack::PopOverlay(Layer* overlay) {

		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay); // it 是 vector<Layer*>::iterator
		if (it != m_Layers.end()) {

			overlay->OnDetach();
			m_Layers.erase(it);

		}

	}
}