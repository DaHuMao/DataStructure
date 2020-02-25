#include<vector>
template<class T, class elem>
class segTree {
public:
	segTree(std::vector<T>& v1) :ori(v1), node(makeVec(v1)) {
    std::vector<int> point;
		init(ori, point, 0);
	};
	void update(std::vector<int> point, elem val) {
		pointChange(point);
		auto val1 = val - assign(ori, point, 0, val, 1);
		treeUpdate(node, point, 0, val1);
	}
	elem sum(std::vector<int> point1, std::vector<int> point2) {
		pointChange(point1);
		pointChange(point2);
		return treeSum(node, point1, point2, 0);
	}
	void updateAdd(std::vector<int> point, elem val) {
		pointChange(point);
		treeUpdate(node, point, 0, val);
		assign(ori, point, 0, val, 2);
	}
private:
	void pointChange(std::vector<int>& point) {
		for (int& e : point)
			++e;
	}
	template<class vecType>
	std::vector<vecType> makeVec(std::vector<vecType>& v) {
		return std::vector<vecType>(v.size() + 1, makeVec(v[0]));
	}
	elem makeVec(elem& e) {
		return elem();
	}
	template<class vecType>
	void init(std::vector<vecType>& v, std::vector<int>& point, int n) {
		if (point.size()<n + 1)
			point.push_back(0);
		for (int i = 0; i < v.size(); ++i) {
			point[n] = i + 1;
			init(v[i], point, n + 1);
		}
	}
	void init(elem& e, std::vector<int>& point, int n) {
		treeUpdate(node, point, 0, e);
	}
	template<class vecType>
	elem assign(std::vector<vecType>& v, std::vector<int>& point, int n, elem& val, int flag) {
		return assign(v[point[n] - 1], point, n + 1, val, flag);
	}
	elem assign(elem& e1, std::vector<int>& point, int n, elem& val, int flag) {
		auto tmp = e1;
		if (flag == 1)
			e1 = val;
		else if (flag == 2)
			e1 = e1 + val;
		return tmp;
	}
	template<class vectype>
	void treeUpdate(std::vector<vectype>& v, std::vector<int>& point, int n, elem& val) {
		int index = point[n];
		while (index < v.size()) {
			treeUpdate(v[index], point, n + 1, val);
			index += index&(-index);
		}
	}
	void treeUpdate(elem& e, std::vector<int>& point, int n, elem& val) {
		e = e + val;
	}
	template<class vectype>
	elem treeSum(std::vector<vectype>& v, std::vector<int>& point1, std::vector<int>& point2, int n) {
		elem ans = elem();
		int i = std::max(point1[n], point2[n]), j = std::min(point1[n], point2[n]) - 1;
		while (i > 0) {
			ans += treeSum(v[i], point1, point2, n + 1);
			i -= i&(-i);
		}
		while (j > 0) {
			ans -= treeSum(v[j], point1, point2, n + 1);
			j -= j&(-j);
		}
		return ans;
	}
	elem treeSum(elem& e, std::vector<int>& point1, std::vector<int>& point2, int n) {
		return e;
	}
  std::vector<T> ori;
  std::vector<T> node;
};
