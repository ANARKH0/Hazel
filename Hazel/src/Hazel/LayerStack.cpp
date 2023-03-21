#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel {

	LayerStack::LayerStack() {

		m_LayerInsert = m_Layers.begin();
	}
 
	LayerStack::~LayerStack() {

		for (Layer* layer : m_Layers) { // ��Ӧ���������ڽ���ʱ�Բ�����������ڲ����ʱֻ����ջ���������٣�������
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer) {

		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer); // ���� layerInsert �����ʵ�л�, �ڲ���ǰ��m_LayerInsert������
		layer->OnAttach();

	}

	void LayerStack::PushOverlay(Layer* overlay) {

		m_Layers.emplace_back(overlay);   // ���ǲ���ջ������,vector����ĩβ
		overlay->OnAttach();

	}

	void LayerStack::PopLayer(Layer* layer) {

		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer); // it �� vector<Layer*>::iterator
		if (it != m_Layers.end()) {

			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsert--; // vector<Layer*>::iterator type ֧�� -- ����

		}
	}

	void LayerStack::PopOverlay(Layer* overlay) {

		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay); // it �� vector<Layer*>::iterator
		if (it != m_Layers.end()) {

			overlay->OnDetach();
			m_Layers.erase(it);

		}

	}
}