#ifdef _UNIX_
#include <csignal>
#include <fstream>
#include <ostream>
#endif
#include <cmath>
#include <ctime>
#include <exception>
#include <iostream>
#include <vector>

#include "map.hpp"
#include "rosetta_avl.h"

#ifdef _UNIX_
bool run_state = 1;

void sigint_handler(int code) {
	run_state = 0;
}
#endif

bool is_duplicate(int vin, std::vector<int>& vout, size_t size, int index) {
	if (size > vout.max_size()) {
		throw "Exceeds the maximum size that could be allocated for std::vector";
	}
	if (!vout[vin]) {
		vout[vin] = 1;
		return 0;
	}
	return 1;
}

int generate_random_int(int min, int max) {
	return min + (rand() % (int)(max - min + 1));
}

void generate_random_vector(std::vector<int>& out, const int min, 
		const int max, const size_t max_size) {
	size_t size = generate_random_int(0, max_size);
	for(size_t i = 0; i < size; ++i) {	
		int num = generate_random_int(min, max);
		out.push_back(num);
	}
}

void show(const std::vector<int>& out) {
	for(size_t i = 0; i < out.size(); ++i) {
		std::cout << out[i] << ", ";
	}
	std::cout << "\n";
}

bool check_height(int n, int height) {
    if (height < ceil(log2(n + 1))) {
        return 1;
    }

    if (height > floor(1.44f * log2(n + 2) - 0.328f)) {
        return 1;
    }
    return 0;
}

bool check_balance(nstd::map<int, int>& map) {
        size_t sz = map.size();
        size_t height = map.max_height();
        if(check_height(sz, height)) {
                std::cout << "Error: Unbalanced tree\n";
                std::cout << "Info: Height of tree: '" << height <<"'\n";
                std::cout << "Info: Element count into the tree: '" << sz <<"'\n";
                return 1;
        }
        return 0;
}

bool check_inorder_start(const std::vector<int>& out, nstd::map<int, int>& map) {
    if(out.empty()) {
        if(map.inorder_start() != map.end()) {
            std::cout << "Info: 'inorder_start'- Fail.\n";
            std::cout << "Info: empty tree dosen't have 'start' element.\n";
            return 1;
        }
        std::cout << "Info: 'inorder_start'- Pass.\n";
        std::cout << "Info: An empty tree.\n";
        return 0;
    }
    //int start_item = map.inorder_start()->get_entry().first;
    int start_item = (*map.inorder_start()).first;
    if(out[0] != start_item) {
        std::cout << "Info: 'inorder_start'i- Fail.\n";
        std::cout << "Info: The start element is: " << out[0] << "\n;";
        std::cout << "Info: The output of 'inorder_start': "<< start_item << "\n"; 
        std::cout << "Info: Incorrect inorder traversal: ";
        show(out);
        return 1;
    }
    std::cout << "Info: 'inorder_start'- Pass.\n";
    return 0;
}

bool check_preorder_start(const std::vector<int>& out, nstd::map<int, int>& map) {
    if(out.empty()) {
        if(map.preorder_start() != map.end()) {
            std::cout << "Info: 'preorder_start'- Fail.\n";
            std::cout << "Info: An empty tree dosen't have 'start' element.\n";
            return 1;
        }
        std::cout << "Info: 'preorder_start'- Pass.\n";
        std::cout << "Info: An empty tree.\n";
        return 0;
    }
    int start_item = (*map.preorder_start()).first;
    if(out[0] != start_item) {
        std::cout << "Info: 'preorder_start'- Fail.\n";
        std::cout << "Info: The start element is: " << out[0] << "\n;";
        std::cout << "Info: The output of 'preorder_start': "<< start_item << "\n"; 
        std::cout << "Info: Incorrect preorder traversal: ";
        show(out);
        return 1;
    }
    std::cout << "Info: 'preorder_start'- Pass.\n";
    return 0;
}

bool check_postorder_start(const std::vector<int>& out, nstd::map<int, int>& map) {
    if(out.empty()) {
        if(map.postorder_start() != map.end()) {
            std::cout << "Info: 'postorder_start'- Fail.\n";
            std::cout << "Info: An empty tree dosen't have 'start' element.\n";
            return 1;
        }
        std::cout << "Info: 'postorder_start'- Pass.\n";
        std::cout << "Info: An empty tree.\n";
        return 0;
    }
    int start_item = (*map.postorder_start()).first;
    if(out[0] != start_item) {
        std::cout << "Info: 'postorder_start'- Fail.\n";
        std::cout << "Info: The end element is: " << out[0] << "\n";
        std::cout << "Info: The output of 'postorder_start': "<< start_item << "\n"; 
        std::cout << "Info: Incorrect postorder traversal: ";
        show(out);
        return 1;
    }
    std::cout << "Info: 'postorder_start'- Pass.\n";
    return 0;
}

bool check_inorder_end(const std::vector<int>& out, nstd::map<int, int>& map) {
    if(out.empty()) {
        if(map.inorder_end() != map.end()) {
            std::cout << "Info: 'inorder_end'- Fail.\n";
            std::cout << "Info: An empty tree dosen't have 'end' element.\n";
            return 1;
        }
        std::cout << "Info: 'inorder_end'- Pass.\n";
        std::cout << "Info: An empty tree.\n";
        return 0;
    }
    int end_item = (*map.inorder_end()).first;
    if(out[out.size() - 1] != end_item) {
        std::cout << "Info: 'inorder_end'- Fail.\n";
        std::cout << "Info: The end element is: " << out[out.size() - 1] << "\n;";
        std::cout << "Info: The output of 'inorder_end': "<< end_item << "\n"; 
        std::cout << "Info: Incorrect inorder traversal: ";
        show(out);
        return 1;
    }
    std::cout << "Info: 'inorder_end'- Pass.\n";
    return 0;
}

bool check_preorder_end(const std::vector<int>& out, nstd::map<int, int>& map) {
    if(out.empty()) {
        if(map.preorder_end() != map.end()) {
            std::cout << "Info: 'preorder_end'- Fail.\n";
            std::cout << "Info: An empty tree dosen't have 'end' element.\n";
            return 1;
        }
        std::cout << "Info: 'preorder_end'- Pass.\n";
        std::cout << "Info: An empty tree.\n";
        return 0;
    }
    int end_item = (*map.preorder_end()).first;
    if(out[out.size() - 1] != end_item) {
        std::cout << "Info: 'preorder_end'- Fail.\n";
        std::cout << "Info: The end element is: " << out[out.size() - 1] << "\n;";
        std::cout << "Info: The output of 'preorder_end': "<< end_item << "\n"; 
        std::cout << "Info: Incorrect preorder traversal: ";
        show(out);
        return 1;
    }
    std::cout << "Info: 'preorder_end'- Pass.\n";
    return 0;
}

bool check_postorder_end(const std::vector<int>& out, nstd::map<int, int>& map) {
    if(out.empty()) {
        if(map.preorder_end() != map.end()) {
            std::cout << "Info: 'postorder_end'- Fail.\n";
            std::cout << "Info: An empty tree dosen't have 'end' element.\n";
            return 1;
        }
        std::cout << "Info: 'postorder_end'- Pass.\n";
        std::cout << "Info: An empty tree.\n";
        return 0;
    }
    int end_item = (*map.postorder_end()).first;
    if(out[out.size() - 1] != end_item) {
        std::cout << "Info: 'postorder_end'- Fail.\n";
        std::cout << "Info: The end element is: " << out[out.size() - 1] << "\n;";
        std::cout << "Info: The output of 'postorder_end': "<< end_item << "\n"; 
        std::cout << "Info: Incorrect postorder traversal: ";
        show(out);
        return 1;
    }
    std::cout << "Info: 'postorder_end'- Pass.\n";
    return 0;
}

bool insert_random_item(nstd::map<int, int>& map, AVLtree<int>* set_golden, int min, int max) {
        int random_int = generate_random_int(min, max);        
        map.insert(random_int);
        set_golden->insert(random_int);
        if(check_balance(map)) {
                return 1;
        }
        return 0;
}

bool remove_random_item(nstd::map<int, int>& map, AVLtree<int>* golden, const std::vector<int>& out, int min, int max) {
        int random_int = generate_random_int(min, max);        
        map.remove(random_int);
        golden->deleteKey(random_int);
        if(check_balance(map)) {
                return 1;
        }
        return 0;
}

bool init_sets(nstd::map<int, int>& map, AVLtree<int>* set_golden, int min, int max, size_t max_size) {
        std::vector<int> out;
        generate_random_vector(out, min, max, max_size);
        for(auto const& item : out) {
                map.insert(item);
                set_golden->insert(item);
                if(check_balance(map)) {
                        std::cout << "Info: The initial vector: " << "\n";
                        show(out);
                        return 1;
                }
        }
        if(!out.empty()) {
                if(remove_random_item(map, set_golden, out, min, out.size() - 1)) {
                        return 1;
                }
                if(insert_random_item(map, set_golden, min, max)) {
                        return 1;
                }
                if(remove_random_item(map, set_golden, out, min, out.size() - 1)) {
                        return 1;
                }
                if(insert_random_item(map, set_golden, min, max)) {
                        return 1;
                }
        }
        return 0;
}
bool inorder_stress_test(nstd::map<int, int>& map, const std::vector<int>& golden) {
        std::vector<int> out;
        map.traverse_inorder(out);
        if(out == golden) {
                std::cout << "Info: 'inorder_stress_test'- Pass.\n ";
        } else {
                std::cout << "Info: 'inorder_stress_test'- Fail.\n ";
                std::cout << "\tInfo: Actual:\n\t";
                show(out);
                std::cout << "\tInfo: Golden:\n\t";
                show(golden);
                return 1;
        }
        return 0;
}

bool preorder_stress_test(nstd::map<int, int>& map, const std::vector<int>& golden) {
        std::vector<int> out;
        map.traverse_preorder(out);
        if(out == golden) {
                std::cout << "Info: 'preorder_stress_test'- Pass.\n ";
        } else {
                std::cout << "Info: 'preorder_stress_test'- Fail.\n ";
                std::cout << "\tInfo: Actual:\n\t";
                show(out);
                std::cout << "\tInfo: Golden:\n\t";
                show(golden);
                return 1;
        }
        return 0;
}

bool postorder_stress_test(nstd::map<int, int>& map, const std::vector<int>& golden) {
        std::vector<int> out;
        map.traverse_postorder(out);
        if(out == golden) {
                std::cout << "Info: 'postorder_stress_test'- Pass.\n ";
        } else {
                std::cout << "Info: 'postorder_stress_test'- Fail.\n ";
                std::cout << "\tInfo: Actual:\n\t";
                show(out);
                std::cout << "\tInfo: Golden:\n\t";
                show(golden);
                return 1;
        }
        return 0;
}

bool inorder_iteration_based_stress_test(nstd::map<int, int>& map, const std::vector<int>& golden) {
        std::vector<int> out;
        nstd::map<int, int>::inorder_iterator it = map.begin();
        for(; it != map.end(); ++it) {
                out.push_back((*it).first);
        }
        if(out == golden) {
                std::cout << "Info: 'inorder_iteration_based_stress_test'- Pass.\n ";
        } else {
                std::cout << "Info: 'inorder_iteration_based_stress_test'- Fail.\n ";
                std::cout << "\tInfo: Actual:\n\t";
                show(out);
                std::cout << "\tInfo: Golden:\n\t";
                show(golden);
                return 1;
        }
        return 0;
}

bool preorder_iteration_based_stress_test(nstd::map<int, int>& map, const std::vector<int>& golden) {
        std::vector<int> out;
        nstd::map<int, int>::preorder_iterator it = map.begin();
        for(; it != map.end(); ++it) {
                out.push_back((*it).first);
        }
        if(out == golden) {
                std::cout << "Info: 'preorder_iteration_based_stress_test'- Pass.\n ";
        } else {
                std::cout << "Info: 'preorder_iteration_based_stress_test'- Fail.\n ";
                std::cout << "\tInfo: Actual:\n\t";
                show(out);
                std::cout << "\tInfo: Golden:\n\t";
                show(golden);
                return 1;
        }
        return 0;
}

bool postorder_iteration_based_stress_test(nstd::map<int, int>& map, const std::vector<int>& golden) {
        std::vector<int> out;
        nstd::map<int, int>::postorder_iterator it = map.begin();		
        for(; it != map.end(); ++it) {
                out.push_back((*it).first);
        }
        if(out == golden) {
                std::cout << "Info: 'postorder_iteration_based_stress_test'- Pass.\n ";
        } else {
                std::cout << "Info: 'postorder_iteration_based_stress_test'- Fail.\n ";
                std::cout << "\tInfo: Actual:\n\t";
                show(out);
                std::cout << "\tInfo: Golden:\n\t";
                show(golden);
                return 1;
        }
        return 0;
}

bool inorder_const_iteration_based_stress_test(nstd::map<int, int>& map, const std::vector<int>& golden) {
	std::vector<int> out;
	nstd::map<int, int>::const_inorder_iterator it = map.cbegin();
	for (; it != map.cend(); ++it) {
		out.push_back((*it).first);
	}
	if (out == golden) {
		std::cout << "Info: 'inorder_const_iteration_based_stress_test'- Pass.\n ";
	}
	else {
		std::cout << "Info: 'inorder_const_iteration_based_stress_test'- Fail.\n ";
		std::cout << "\tInfo: Actual:\n\t";
		show(out);
		std::cout << "\tInfo: Golden:\n\t";
		show(golden);
		return 1;
	}
	return 0;
}

bool preorder_const_iteration_based_stress_test(nstd::map<int, int>& map, const std::vector<int>& golden) {
	std::vector<int> out;
	nstd::map<int, int>::const_preorder_iterator it = map.cbegin();
	for (; it != map.cend(); ++it) {
		out.push_back((*it).first);
	}
	if (out == golden) {
		std::cout << "Info: 'preorder_const_iteration_based_stress_test'- Pass.\n ";
	}
	else {
		std::cout << "Info: 'preorder_const_iteration_based_stress_test'- Fail.\n ";
		std::cout << "\tInfo: Actual:\n\t";
		show(out);
		std::cout << "\tInfo: Golden:\n\t";
		show(golden);
		return 1;
	}
	return 0;
}

bool postorder_const_iteration_based_stress_test(nstd::map<int, int>& map, const std::vector<int>& golden) {
	std::vector<int> out;
	nstd::map<int, int>::const_postorder_iterator it = map.cbegin();
	for (; it != map.cend(); ++it) {
		out.push_back((*it).first);
	}
	if (out == golden) {
		std::cout << "Info: 'postorder_const_iteration_based_stress_test'- Pass.\n ";
	}
	else {
		std::cout << "Info: 'postorder_const_iteration_based_stress_test'- Fail.\n ";
		std::cout << "\tInfo: Actual:\n\t";
		show(out);
		std::cout << "\tInfo: Golden:\n\t";
		show(golden);
		return 1;
	}
	return 0;
}

bool insert_test(nstd::map<int, int>& map, int min, int max, size_t max_size) {
	int size = generate_random_int(min, max);
	std::vector<int> vin{};		
	std::vector<int> vout(max + 1, 0);
	for(int i = 0; i < size; ++i) {				
		int item = generate_random_int(min, max);							    
		if(!is_duplicate(item, vout, max, i)) {
			vin.push_back(item);
		}
		map.insert(item);				
		if(check_balance(map)) {
			std::cout << "Info: 'insert_test'- Fail.\n ";
			return 1;
		}                
		nstd::map<int, int>::inorder_iterator it = map.find(item);				
		if (it == map.end() && vin.size() != map.size()) {
			std::cout << "Info: 'insert_test'- Fail.\n ";
			return 1;
		}
	}
	std::cout << "Info: 'insert_test'- Pass.\n ";
	return 0;
}

bool remove_test(nstd::map<int, int>& map) {
        std::vector<int> items{};
        map.traverse_inorder(items);
        for(auto const& item: items) {
                size_t size = map.size();
                map.remove(item);
                if(check_balance(map)) {
                        std::cout << "Info: 'remove_test'- Fail.\n ";
                        return 1;
                }
                if(size != map.size() + 1) {
                        std::cout << "Info: 'remove_test'- Fail.\n ";
                        return 1;
                }
        }
        std::cout << "Info: 'remove_test'- Pass.\n ";
        return 0;
}

bool inorder_iterator_copy_test(nstd::map<int, int>& map, int min, int max) {
	nstd::map<int, int>::inorder_iterator it = map.begin();
	for(; it != map.end(); ++it) {
		nstd::map<int, int>::inorder_iterator it_second(it);
		int item = generate_random_int(min, max);
		(*it_second).second = item;
		if((*it).second != (*it_second).second) {
			std::cout << "Error: Incorrect value copy of iterator. 'inorder_iterator_copy_test'- Fail.\n";
			return 1;
		}
	}
	std::cout << "Info: 'inorder_iterator_copy_test'- Pass.\n ";
	return 0;
}

bool preorder_iterator_copy_test(nstd::map<int, int>& map, int min, int max) {
	nstd::map<int, int>::preorder_iterator it = map.begin();
	for(; it != map.end(); ++it) {
		nstd::map<int, int>::preorder_iterator it_second(it);
		int item = generate_random_int(min, max);
		(*it_second).second = item;
		if((*it).second != (*it_second).second) {
			std::cout << "Error: Incorrect value copy of iterator. 'preorder_iterator_copy_test'- Fail.\n";
			return 1;
		}
	}
	std::cout << "Info: 'preorder_iterator_copy_test'- Pass.\n ";
	return 0;
}

bool postorder_iterator_copy_test(nstd::map<int, int>& map, int min, int max) {
	nstd::map<int, int>::postorder_iterator it = map.begin();
	for(; it != map.end(); ++it) {
		nstd::map<int, int>::postorder_iterator it_second(it);
		int item = generate_random_int(min, max);
		(*it_second).second = item;
		if((*it).second != (*it_second).second) {
			std::cout << "Error: Incorrect value copy of iterator. 'postorder_iterator_copy_test'- Fail.\n";
			return 1;
		}
	}
	std::cout << "Info: 'postorder_iterator_copy_test'- Pass.\n ";
	return 0;
}

bool stress_test(const int min, const int max, const size_t max_size) {
        int i = 0;
#if defined(_UNIX_) && !defined(_LIMIT_)
        while(run_state) {
#elif defined(_UNIX_) && defined(_LIMIT_)
        while (run_state && i < _LIMIT_) {
#elif !defined(_UNIX_) && !defined(_LIMIT_)
        while(1) {
#elif !defined(_UNIX_) && defined(_LIMIT_)
        while (i < _LIMIT_) {
#endif
                nstd::map<int, int> map;
                AVLtree<int>* set_golden = new AVLtree<int>();
                std::cout << "\n##########  No:" << i << " iteration started. ##########\n";
                if(insert_test(map, min, max, max_size)) {
                        return 1;
                }
                if(remove_test(map)) {
                        return 1;
                }
                if(init_sets(map, set_golden, min, max, max_size)) {
                        return 1;
                }
                std::vector<int> inorder_golden;
                set_golden->inorder(inorder_golden);
                std::vector<int> preorder_golden;
                set_golden->preorder(preorder_golden);
                std::vector<int> postorder_golden;
                set_golden->postorder(postorder_golden);
                std::cout << "\n";
                if(check_inorder_start(inorder_golden, map)) {
                        return 1;
                }
                if(check_inorder_end(inorder_golden, map)) {
                        return 1;
                }
                if(check_preorder_start(preorder_golden, map)) {
                        return 1;
                }
                if(check_preorder_end(preorder_golden, map)) {
                        return 1;
                }
                if(check_postorder_start(postorder_golden, map)) {
                        return 1;
                }
                if(check_postorder_end(postorder_golden, map)) {
                        return 1;
                }
                if(inorder_stress_test(map, inorder_golden)) {
                        return 1;
                }
                if(preorder_stress_test(map, preorder_golden)) {
                        return 1;
                }
                if(postorder_stress_test(map, postorder_golden)) {
                        return 1;
                }
                if(inorder_iteration_based_stress_test(map, inorder_golden)) {
                        return 1;
                }
                if(preorder_iteration_based_stress_test(map, preorder_golden)) {
                        return 1;
                }
                if(postorder_iteration_based_stress_test(map, postorder_golden)) {
                        return 1;
		}
		if(inorder_const_iteration_based_stress_test(map, inorder_golden)) {
			return 1;
		}
		if(preorder_const_iteration_based_stress_test(map, preorder_golden)) {
			return 1;
		}
		if(postorder_const_iteration_based_stress_test(map, postorder_golden)) {
			return 1;
		}
		if(inorder_iterator_copy_test(map, min, max)) {
			return 1;
		}
		if(preorder_iterator_copy_test(map, min, max)) {
			return 1;
		}
		if(postorder_iterator_copy_test(map, min, max)) {
			return 1;
		}
                std::cout << "\n##########  No:" << i << " iteration done.    ##########\n";
                delete set_golden;
                ++i;
        }
        std::cout << "Info: Total count of iterations: " << i << "\n";
#ifdef _UNIX_
        if(run_state) {
                return 0;
        }
#endif
        return 0;
}

int main() {	
        srand(time(0));
#ifdef _UNIX_
        std::ofstream log_file("test.log", std::ios::out|std::ios::app);
        std::streambuf* cout_stream_buf = std::cout.rdbuf();
        std::streambuf* file_stream_buf = log_file.rdbuf();
        std::cout.rdbuf(file_stream_buf); 
#endif
        if(stress_test(0, 1000, 300)) {
                std::cout << "\nTest status: Fail.\n";
        } else {
                std::cout << "\nTest status: Pass.\n";
        }    
#ifdef _UNIX_
        std::cout.rdbuf(cout_stream_buf);
        log_file.close();
#endif
        return 0;
}
