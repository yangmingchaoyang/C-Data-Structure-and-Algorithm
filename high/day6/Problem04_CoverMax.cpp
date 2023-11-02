/*
平面内有n个矩形, 第i个矩形的左下角坐标为(x1[i], y1[i]), 右上角坐标为(x2[i],
y2[i])。如果两个或者多个矩形有公共区域则认为它们是相互重叠的(不考虑边界和角
落)。请你计算出平面内重叠矩形数量最多的地方,有多少个矩形相互重叠。
*/
#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include<list>
using namespace std;


class Rectangle{
public:
    int up;
    int down;
    int left;
    int right;

    Rectangle(){};
    Rectangle(int up,int down,int left,int right){
        this->up=up;
        this->down=down;
        this->left=left;
        this->right=right;
    }
};

// 左边界比较器
//升序
struct LeftComparator {
    bool operator()(const Rectangle& rect1, const Rectangle& rect2) const {
        return rect1.left < rect2.left;
    }
};

// 右边界比较器
struct RightComparator {
    bool operator()(const Rectangle& rect1, const Rectangle& rect2) const {
        return rect1.right < rect2.right;
    }
};

// 下边界比较器
//大的排在前面
struct DownComparator {
    bool operator()(const Rectangle& rect1, const Rectangle& rect2) const {
        return rect1.down < rect2.down;
    }
};

void removeLowerOnCurDown(std::set<Rectangle, LeftComparator>& set, int curDown) {
    std::vector<Rectangle> removes;
    for (const Rectangle& rec : set) {
        if (rec.up <= curDown) {
            removes.push_back(rec);
        }
    }
    for (const Rectangle& rec : removes) {
        set.erase(rec);
    }
}

void removeLeftOnCurLeft(std::set<Rectangle, RightComparator>& rightOrdered, int curLeft) {
    std::vector<Rectangle> removes;
    for (const Rectangle& rec : rightOrdered) {
        if (rec.right > curLeft) {
            break;
        }
        removes.push_back(rec);
    }
    for (const Rectangle& rec : removes) {
        rightOrdered.erase(rec);
    }
}

int maxCover(std::vector<Rectangle>& recs) {
    if (recs.empty()) {
        return 0;
    }

    std::sort(recs.begin(), recs.end(), DownComparator());//最低开始
    std::set<Rectangle, LeftComparator> leftOrdered;//最左开始
    int ans = 0;
    
    for (int i = 0; i < recs.size(); i++) {
        int curDown = recs[i].down;
        int index = i;
        while (recs[index].down == curDown) {//找连续的底相同的元素
            leftOrdered.insert(recs[index]);
            index++;
        }
        i = index;
        removeLowerOnCurDown(leftOrdered, curDown);

        std::set<Rectangle, RightComparator> rightOrdered;//最左边的元素开始
        for (const Rectangle& rec : leftOrdered) {
            removeLeftOnCurLeft(rightOrdered, rec.left);
            rightOrdered.insert(rec);
            ans = std::max(ans, static_cast<int>(rightOrdered.size()));
        }
    }

    return ans;
}

int main() {
    std::vector<Rectangle> recs = {
        {1, 0, 0, 2},
        {2, 1, 1, 3},
        {3, 2, 2, 4},
        {4, 3, 3, 5}
    };
    
    int result = maxCover(recs);
    std::cout << "Maximum cover: " << result << std::endl;
    
    return 0;
}