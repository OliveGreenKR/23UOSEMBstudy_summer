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

template<class T>
void Vec<T>::create() {
	_data = _avail = _limit = nullptr;
}

template<class T>
void Vec<T>::create(size_type n , const T& val) {
	_data = _alloc.allocate(n);
	_limit = _avail = _data + n;
	::uninitialized_fill(_data, _avail, val); //[data,_avail) val�� �ʱ�ȭ
}

template<class T>
void Vec<T>::create(const_iterator i, const_iterator j ) {
	_data = _alloc.allocate(j-1);
	_limit = _avail = ::uninitialized_copy(i, j, _data); 
	//[i,j)�� _dat�� �ʱ�ȭ ���� ������ ����� ������ ����Ű�� ������ ��ȯ
}

template<class T>
void Vec<T>::uncreate() {
	if (_data != nullptr) {
		//�������� �Ҹ�
		iterator it = _avail;
		while (it != _data)
			_alloc.destroy(--it);

		//������� ��ȯ
		_alloc.deallocate(_data, _limit - _data);
	}

	_data = _limit = _avail = nullptr;
}

template<class T>
void Vec<T>::grow() {
	//���� 2���� ���� �Ҵ�.
	size_type new_size = max(2*(_limit - _data), ptrdiff_t(1));

	//���ο� ������ ����
	iterator new_data = _alloc.allocate(new_size);
	iterator new_avail = ::uninitialized_copy(_data, _avail, new_data);
	//���� ��ȯ
	uncreate();
	//������ �缳��
	_data = new_data;
	_avail = new_avail;
	_limit = _data + new_size;
}

template<class T>
void Vec<T>::unchecked_append(const T& val) {
	_alloc.construct(_avail++, val); //�ʱ�ȭ �Ǿ��������� ������ ��ü ����.
}
