#include "pch.h"
#include "Vec.h"

template<class T>
Vec<T>& Vec<T>::operator=(const Vec& rhs) {
	//�ڰ��Ҵ� ���� Ȯ��
	if (&rhs != this) {
		uncreate(); //�º� �޸� ����

		create(rhs.begin(), rhs.end()); // �캯�� ���� ��Ҹ� �º����� ����.
	}
	return *this; //�º��� ��ü�� ������ ����
}
