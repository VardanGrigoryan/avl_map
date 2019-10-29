// Map implementation -*- C++ -*-

// Copyright (C) 2019 
// Author: Vardan Grigoryan. 
//
// This library is free software; you can redistribute it and/or 
// modify it as it published by the author.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

/**
 * @file      nmap.hpp
 * @brief     Map implementation -*- C++ -*-
 * @detail    This library is free software. You can redistribute it and/or modify it as it published by the author
 * @author    Vardan Grigoryan 
*/

#include <cassert>
#include <memory>
#include <vector>

namespace nstd {
    typedef void default_type;
    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC> class CONT,
              typename AllocatorType>
    class map;
    template <typename iter_type>
    struct generic_iterator_traits;
    template <>
    struct generic_iterator_traits<default_type> {
        template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator = std::less,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
              typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
			static typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node*
            start(map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_) {                
				return nullptr;
        }
    };
    struct inorder_iterator_traits;
    template <>
    struct generic_iterator_traits<inorder_iterator_traits> {
        template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator = std::less,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
              typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
        static typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* 
            start(map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_) {
                return _map_->inorder_start_helper();
        }
        template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator = std::less,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
              typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
        static typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* 
            next(map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* _node_) {
                return _map_->inorder_successor(_node_);
        }
        template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator = std::less,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
              typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
        static typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* 
            prev(map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* _node_) {
                return _map_->inorder_predecessor(_node_);
        }
    };
    struct preorder_iterator_traits;
    template <>
    struct generic_iterator_traits<preorder_iterator_traits> {
        template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator = std::less,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
              typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
        static typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* 
            start(map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_) {
                return _map_->preorder_start_helper();
        }
        template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator = std::less,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
              typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
        static typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* 
            next(map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* _node_) {
                return _map_->preorder_successor(_node_);
        }
        template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator = std::less,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
              typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
        static typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* 
            prev(map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* _node_) {
                return _map_->preorder_predecessor(_node_);
        }
    };
    struct postorder_iterator_traits;
    template <>
    struct generic_iterator_traits<postorder_iterator_traits> {
        template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator = std::less,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
              typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
        static typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* 
            start(map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_) {
                return _map_->postorder_start_helper();
        }
        template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator = std::less,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
              typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
        static typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* 
            next(map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* _node_) {
                return _map_->postorder_successor(_node_);
        }
        template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator = std::less,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
              typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
        static typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* 
            prev(map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* _node_) {
                return _map_->postorder_predecessor(_node_);
        }
    };
	template <typename iter_type>
	struct const_generic_iterator_traits;
	template <>
	struct const_generic_iterator_traits<default_type> {
		template <typename KeyType,
			typename DataType,
			template <typename> class comparator = std::less,
			template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
			typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
			static const typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node*
			start(map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_) {
			return nullptr;
		}
	};
	template <>
	struct const_generic_iterator_traits<inorder_iterator_traits> {
		template <typename KeyType,
			typename DataType,
			template <typename> class comparator = std::less,
			template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
			typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
			static const typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node*
			start(map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_) {
			return _map_->inorder_start_helper();
		}
		template <typename KeyType,
			typename DataType,
			template <typename> class comparator = std::less,
			template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
			typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
			static const typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node*
			next(map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* _node_) {
			return _map_->inorder_successor(_node_);
		}
		template <typename KeyType,
			typename DataType,
			template <typename> class comparator = std::less,
			template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
			typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
			static const typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node*
			prev(map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* _node_) {
			return _map_->inorder_predecessor(_node_);
		}
	};	
	template <>
	struct const_generic_iterator_traits<preorder_iterator_traits> {
		template <typename KeyType,
			typename DataType,
			template <typename> class comparator = std::less,
			template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
			typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
			static const typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node*
			start(map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_) {
			return _map_->preorder_start_helper();
		}
		template <typename KeyType,
			typename DataType,
			template <typename> class comparator = std::less,
			template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
			typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
			static const typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node*
			next(map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* _node_) {
			return _map_->preorder_successor(_node_);
		}
		template <typename KeyType,
			typename DataType,
			template <typename> class comparator = std::less,
			template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
			typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
			static const typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node*
			prev(map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* _node_) {
			return _map_->preorder_predecessor(_node_);
		}
	};	
	template <>
	struct const_generic_iterator_traits<postorder_iterator_traits> {
		template <typename KeyType,
			typename DataType,
			template <typename> class comparator = std::less,
			template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
			typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
			static const typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node*
			start(map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_) {
			return _map_->postorder_start_helper();
		}
		template <typename KeyType,
			typename DataType,
			template <typename> class comparator = std::less,
			template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
			typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
			static const typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node*
			next(map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* _node_) {
			return _map_->postorder_successor(_node_);
		}
		template <typename KeyType,
			typename DataType,
			template <typename> class comparator = std::less,
			template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
			typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
			static const typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node*
			prev(map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* _node_) {
			return _map_->postorder_predecessor(_node_);
		}
	};
    
	template <typename iter_type>
	struct base_iterator {};

        /**
         * @class  uncopyable 
         * @brief  A base class with private/deleted copy/assignement
         * @detail Inherit privately from this base class in order to make derived classes uncopyable
        */ 
	class uncopyable
	{
	protected:
		uncopyable() {}
		~uncopyable() {}
	private:
		uncopyable(const uncopyable&);
		uncopyable& operator=(const uncopyable&);
	};
    
    /**
     * @class  map
     * @tparam KeyType The type of key
     * @tparam DataType The type of data
     * @tparam comparator A template template parameter which indicates which comparator should be used during comparisions
     * @tparam CONT A default container which will be used to sore the ordered datas which are results of different ways of tree traversals
     * @param AllocatorType Indicates an allocator which could be defined in order to make class map allocate its inner nodes using this allocator
     * @brief  Key/value based associative data structure
     * @detail Container like implementation of dictionary using AVL tree data structure
    */ 
    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator = std::less,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT = std::vector,
              typename AllocatorType = std::allocator<std::pair<const KeyType, DataType>>>
    class map : private uncopyable {	
	private:
		class Node;
		typedef AllocatorType _value_allocator;
		typedef std::allocator_traits<_value_allocator> _value_allocator_traits;
		typedef typename _value_allocator_traits::template rebind_traits<Node> _node_allocator_traits;
		typedef typename _node_allocator_traits::allocator_type _node_allocator_type;
		_node_allocator_type alloc;
            class Node {
                public:
                    Node* parent;
                    std::unique_ptr<Node> left;
                    std::unique_ptr<Node> right;
                    std::pair<KeyType, DataType> entry;
                public:
                    Node() noexcept: parent(nullptr),
                                     left(nullptr),
                                     right(nullptr) {
                    }
                    explicit Node(const KeyType& key) noexcept : parent(nullptr),
                                                                 left(nullptr),
                                                                 right(nullptr) {
                        entry.first = key;
                     }     
                    Node(const KeyType& key, const DataType& data): parent(nullptr),
                                                                    left(nullptr), 
                                                                    right(nullptr),
                                                                    entry(std::make_pair(key, data)) {
                    }      
                    explicit Node(const std::pair<KeyType, DataType>& _pair_): parent(nullptr), 
                                                                               left(nullptr), 
                                                                               right(nullptr),
                                                                               entry(_pair_) {
                    }
                    std::pair<KeyType, DataType>& get_entry() {
                        return entry;
                    }
            };
        private:
            int height(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node);
            typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* get_min(const typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node);
            typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* get_max(const typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node);
            void insert(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node);
            void insert_helper(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* parent, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node*& node);            
            typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* find(const KeyType& key, void*);				
            typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* find_helper(const typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* parent_node, const KeyType key);
            void transplant(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* second_node);
            std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node> left_rotate(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node);
            std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node> right_rotate(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node);
            std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node> left_right_rotate(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node);
            std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node> right_left_rotate(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node);
            void check_balance(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node);
            std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node> rebalance(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node);
            typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* inorder_successor(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node);
            typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* preorder_successor(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node);
            typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* postorder_successor(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node);
            typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* inorder_predecessor(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node);
            typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* postorder_predecessor(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node);
            typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* preorder_predecessor(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node);
            typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* inorder_end_helper();
            typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* preorder_end_helper();
            typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* postorder_end_helper();
            typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* inorder_start_helper();
            typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* preorder_start_helper();
            typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* postorder_start_helper();
            void traverse_inorder_helper(std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node>& node, 
                    std::vector<KeyType>& out);
            void traverse_preorder_helper(std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node>& node, 
                    std::vector<KeyType>& out);
            void traverse_postorder_helper(std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node>& node, 
                    std::vector<KeyType>& out);        			
        public:
            /**
             * class  map
             * @fn     map
             * @brief  Default constructor
             * @param _alloc A default parameter takes allocator type
             * @return no return value
            */ 
            explicit map(const _node_allocator_type& _alloc = AllocatorType()) : alloc(_alloc), 
                                                                                 current_size(0),
                                                                                 root(nullptr) {}			
            /**
             * class  map
             * @fn     ~map
             * @brief  destructor
             * @return no return value
            */ 
            virtual ~map() {
                if(root) {
                    alloc.destroy(root);
                    alloc.deallocate(root, 1);
                }
            }
            /**
             * class  map
             * @fn     operator[]
             * @brief  Returns the associated value with the given key
             * @param  key A key
             * @return DataType&
            */ 
            DataType& operator[](const KeyType& key) {
                typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node = find(key);
                return node->get_entry().second;
            }
            /**
             * class  map
             * @fn     max_height
             * @brief  Returns the height of tree started from root
             * @return size_t
            */ 
            const size_t max_height();
            /**
             * class  map
             * @fn     insert
             * @brief  Inserts a key with associated default value 0
             * @param  key A key
             * @return void
            */ 
            void insert(const KeyType& key);
            /**
             * class  map
             * @fn     insert
             * @brief  Inserts a key with associated value
             * @param  key A key
             * @param  data A data associated with key
             * @return void
            */ 
            void insert(const KeyType& key, const DataType& data);            
            /**
             * class  map
             * @fn     remove
             * @brief  Removes a node associated with given key
             * @param  key A key
             * @return void
            */ 
            void remove(const KeyType& key);
            /**
             * class  map
             * @fn     destroy
             * @brief  This function is for explicitely destroying the tree.
             *         The implementation is not present in current version of source code.
             * @param  key A key
             * @return void
            */ 
            void destroy();
            /**
             * class  map
             * @fn     traverse_inorder 
             * @brief  Returns inorder traversal 
             * @param  out An output std:vector in which traversal results are saved
             * @return void
            */ 
            void traverse_inorder(std::vector<KeyType>& out);
            /**
             * class  map
             * @fn     traverse_preorder 
             * @brief  Returns preorder traversal 
             * @param  out An output std:vector in which traversal results are saved
             * @return void
            */ 
            void traverse_preorder(std::vector<KeyType>& out);
            /**
             * class  map
             * @fn     traverse_postorder 
             * @brief  Returns postorder traversal 
             * @param  out An output std:vector in which traversal results are saved
             * @return void
            */ 
            void traverse_postorder(std::vector<KeyType>& out);
            /**
             * class  map
             * @fn     size 
             * @brief  Returns the count of elements into map 
             * @return size_t
            */ 
            size_t size() const {
                return current_size;
            }
            /**
             * class  map
             * @fn     empty 
             * @brief  Returns a boolean that indicates whether the map is empty 
             * @return bool
            */ 
            bool empty() const {
                return !(static_cast<bool>(current_size));
            }
        public:
            /**
             * class  generic_iterator 
             * @tparam TraitsType The concreate type of iterator 
             * can take one of these traits types: inorder_iterator_traits, 
             * preorder_iterator_traits, postorder_iterator_traits.
             * @tparam Traits is template argument which is using to specialize an internal generic_iterator_traits class
             * @brief  A nested public generic template class
             * @detail Provides an interface and functionality to iterate over map in specific order
            */ 
            template <typename TraitsType, typename Traits=generic_iterator_traits<TraitsType>>
            class generic_iterator: public base_iterator<TraitsType> {
                private:
                    friend class generic_iterator<inorder_iterator_traits>;
                    friend class generic_iterator<preorder_iterator_traits>;
                    friend class generic_iterator<postorder_iterator_traits>;					
                private:
                    map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_;					
                    typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* _node_;
                private:
                    void increment() {
                        if(!this->_node_) {
                            this->_node_ = Traits::template start<KeyType, DataType, comparator, CONT, AllocatorType>(this->_map_);														
                        }
                        this->_node_ = Traits::template next<KeyType, DataType, comparator, CONT, AllocatorType>(this->_map_, this->_node_);						
                    }
                    void decrement() {
                        if(this->_node_) {
                            this->_node_ = Traits::template prev<KeyType, DataType, comparator, CONT, AllocatorType>(this->_map_, this->_node_);							
                        }
                    }
                public:
                    /**
                     * class  generic_iterator
                     * @fn     generic_iterator 
                     * @brief  An expicit constructor with one argument 
                     * @param  An instance of outer template class map
                    */ 
                    explicit generic_iterator(map<KeyType, DataType, comparator, CONT, AllocatorType>* map_instance) { 											
                        if(map_instance) {
                            this->_map_ = map_instance;							
                        }
                        this->_node_ = nullptr;
                    }					
                    /**
                     * class  generic_iterator
                     * @fn     generic_iterator 
                     * @brief  constructor
                     * @param map_instance An instance of the outer class map
                    */ 
		    generic_iterator(map<KeyType, DataType, comparator, CONT, AllocatorType>* map_instance, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node) {
			    if (map_instance) {
				    this->_map_ = map_instance;							
			    }
			    this->_node_ = node;
		    }
                    /**
                     * class  generic_iterator
                     * @fn     generic_iterator 
                     * @brief  copy constructor
                     * @param  rhs Another instance of the class with the same type
                    */
                    /*
                     * Here for copy/assignements we are performing a shalow copy and this is because of the following two reasons:
                     * 1. First of all we need to have a different iterators pointing to the same actual node
                     *    and any change with one of them is required to be in coherence with all of the remaining 
                     *    iterators. For an exmaple an increment of any separate iterator should cause an
                     *    appropriate increment of others too.
                     * 2. Performing a deep copy will require a memory allocations for new nodes. This in turn will require to
                     *    deep-copy all the mamber unique_ptr's. But from the other hand std::unique_ptr unlike shared_ptr haven't
                     *    standard interface to provide an allocator which will force us to implement make_unique which will take 
                     *    allocator as an argument which is an aditional overhead we want to escape. Besides performing a deep-copy
                     *    of unique_ptr will break the concept of uniqueness of pointer.
                     * */
                    generic_iterator(const generic_iterator<default_type>& rhs) {
                        this->_map_ = rhs._map_;						
                        if(!rhs._node_) {
				this->_node_ = Traits::template start<KeyType, DataType, comparator, CONT, AllocatorType>(this->_map_);														
                        } else {
                                this->_node_ = rhs._node_;
                        }
                    }
                    /**
                     * class  generic_iterator
                     * @fn     operator= 
                     * @brief  An assignement operator
                     * @param  rhs Another instance of the class with the same type
                    */ 
                    generic_iterator& operator=(const generic_iterator<default_type>& rhs) noexcept {
                        if((void*)this != (void*)&rhs) {
                            this->_map_ = rhs._map_;							
                            if(!rhs._node_) {
                                this->_node_ = Traits::template start<KeyType, DataType, comparator, CONT, AllocatorType>(this->_map_);								
                            } else {
                                this->_node_ = rhs._node_;
                            }
                        }
                        return *this;
                    }
                    /**
                     * class  generic_iterator
                     * @fn     operator++ 
                     * @brief  Preincrement operator
                     * @return generic_iterator
                    */ 
                    generic_iterator& operator++() {
                        increment();
                        return *this;
                    }
                    /**
                     * class  generic_iterator
                     * @fn     operator++ 
                     * @brief  Postincrement operator
                     * @return generic_iterator
                    */ 
                    generic_iterator operator++(int) {
                        const generic_iterator temp(*this);
                        increment();
                        return temp;
                    }
                    /**
                     * class  generic_iterator
                     * @fn     operator-- 
                     * @brief  Predecrement operator
                     * @return generic_iterator
                    */ 
                    generic_iterator& operator--() {
                        decrement();
                        return *this;
                    }
                    /**
                     * class  generic_iterator
                     * @fn     operator-- 
                     * @brief  Postdecrement operator
                     * @return generic_iterator
                    */ 
                    generic_iterator operator--(int) {
                        const generic_iterator temp(*this);
                        decrement();
                        return temp;
                    }
                    /**
                     * class  generic_iterator
                     * @fn     operator* 
                     * @brief  operator dereference
                     * @return std::pair<const KeyType&, DataType&>
                    */ 
                    std::pair<const KeyType&, DataType&> operator*() noexcept {
                        if(!this->_node_) {
                            this->_node_ = Traits::template start<KeyType, DataType, comparator, CONT, AllocatorType>(this->_map_);							
                            return {this->_node_->entry.first, this->_node_->entry.second};
                        }
                        if(this->_node_) {
                            return {this->_node_->entry.first, this->_node_->entry.second};
                        }
                        KeyType key;
                        DataType data;
                        return {key, data};
                    }
                    /**
                     * class  generic_iterator
                     * @fn     operator== 
                     * @brief  boolean equal operator 
                     * @return bool indicates whether the two given instances are equal 
                    */ 
                   template <typename iter_type>
                    bool operator==(const generic_iterator<iter_type>& rhs) {												
                        return this->_node_ == rhs._node_;
                    }
                    /**
                     * class  generic_iterator
                     * @fn     operator!= 
                     * @brief  boolean non-equal operator 
                     * @return bool indicates whether the two given instances are equal 
                    */ 
                    template <typename iter_type>
                    bool operator!=(const generic_iterator<iter_type>& rhs) {
                        return !((*this) == rhs);
                    }
            };
            /**
             * @class  const_generic_iterator 
             * @tparam TraitsType The concreate type of iterator 
             * can take one of these traits types: inorder_iterator_traits, 
             * preorder_iterator_traits, postorder_iterator_traits.
             * @tparam Traits is template argument which is using to specialize an internal const_generic_iterator_traits class
             * @brief  A nested public generic template class
             * @detail Provides an interface and functionality to iterate over map in specific order
            */ 
	    template <typename TraitsType, typename Traits = const_generic_iterator_traits<TraitsType>>
	    class const_generic_iterator : public base_iterator<TraitsType> {
		    private:
			    friend class const_generic_iterator<inorder_iterator_traits>;
			    friend class const_generic_iterator<preorder_iterator_traits>;
			    friend class const_generic_iterator<postorder_iterator_traits>;
		    private:
			    map<KeyType, DataType, comparator, CONT, AllocatorType>* _map_;
			    typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* _node_;
		    private:
			    void increment() {
				    if (!this->_node_) {
					    this->_node_ = const_cast<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node*>(Traits::template start<KeyType, DataType, comparator, CONT, AllocatorType>(this->_map_));
				    }
				    this->_node_ = const_cast<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node*>(Traits::template next<KeyType, DataType, comparator, CONT, AllocatorType>(this->_map_, this->_node_));
			    }
			    void decrement() {
				    if (this->_node_) {
					    this->_node_ = const_cast<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node*>(Traits::template prev<KeyType, DataType, comparator, CONT, AllocatorType>(this->_map_, this->_node_));
				    }
			    }
		    public:
                    /**
                     * class  const_generic_iterator
                     * @fn     const_generic_iterator 
                     * @param  An instance of outer template class map
                     * @brief  An expicit constructor with one argument 
                    */ 
                    explicit const_generic_iterator(map<KeyType, DataType, comparator, CONT, AllocatorType>* map_instance) {
                            if (map_instance) {
                                    this->_map_ = map_instance;
                            }
                            this->_node_ = nullptr;
                    }
                    /**
                     * class  const_generic_iterator
                     * @fn     const_generic_iterator 
                     * @brief  constructor
                     * @param map_instance An instance of the outer class map
                    */ 
                    const_generic_iterator(map<KeyType, DataType, comparator, CONT, AllocatorType>* map_instance, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node) {
                            if (map_instance) {
                                    this->_map_ = map_instance;
                            }
                            this->_node_ = node;
                    }
                    /**
                     * class  const_generic_iterator
                     * @fn     const_generic_iterator 
                     * @brief  copy constructor
                     * @param  rhs Another instance of the class with the same type
                    */ 
                    const_generic_iterator(const const_generic_iterator<default_type>& rhs) {
                            this->_map_ = rhs._map_;
                            if (!rhs._node_) {
                                    this->_node_ = const_cast<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node*>(Traits::template start<KeyType, DataType, comparator, CONT, AllocatorType>(this->_map_));
                            }
                            else {
                                    this->_node_ = rhs._node_;
                            }
                    }
                    /**
                     * class  const_generic_iterator
                     * @fn     operator= 
                     * @brief  An assignement operator
                     * @param  rhs Another instance of the class with the same type
                    */ 
                    const_generic_iterator& operator=(const const_generic_iterator<default_type>& rhs) noexcept {
                            if ((void*)this != (void*)&rhs) {
                                    this->_map_ = rhs._map_;
                                    if (!rhs._node_) {
                                            this->_node_ = Traits::template start<KeyType, DataType, comparator, CONT, AllocatorType>(this->_map_);
                                    }
                                    else {
                                            this->_node_ = rhs._node_;
                                    }
                            }
                            return *this;
                    }
                    /**
                     * class  const_generic_iterator
                     * @fn     operator++ 
                     * @brief  Preincrement operator
                     * @return const_generic_iterator
                    */ 
                    const_generic_iterator& operator++() {
                            increment();
                            return *this;
                    }
                    /**
                     * class  const_generic_iterator
                     * @fn     operator++ 
                     * @brief  Postincrement operator
                     * @return const_generic_iterator
                    */ 
                    const_generic_iterator operator++(int) {
                            const_generic_iterator temp(*this);
                            increment();
                            return temp;
                    }
                    /**
                     * class  const_generic_iterator
                     * @fn     operator-- 
                     * @brief  Predecrement operator
                     * @return const_generic_iterator
                    */ 
                    const_generic_iterator& operator--() {
                            decrement();
                            return *this;
                    }
                    /**
                     * class  const_generic_iterator
                     * @fn     operator-- 
                     * @brief  Postdecrement operator
                     * @return const_generic_iterator
                    */ 
                    const_generic_iterator operator--(int) {
                            const_generic_iterator temp(*this);
                            decrement();
                            return temp;
                    }
                    /**
                     * class  const_generic_iterator
                     * @fn     operator* 
                     * @brief  operator dereference
                     * @return std::pair<const KeyType&, DataType&>
                    */ 
                    const std::pair<const KeyType&, const DataType&> operator*() noexcept {
			    if (!this->_node_) {
				    this->_node_ = const_cast<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node*>(Traits::template start<KeyType, DataType, comparator, CONT, AllocatorType>(this->_map_));						
				    return { this->_node_->entry.first, this->_node_->entry.second };
			    }
			    if (this->_node_) {						
				    return { this->_node_->entry.first, this->_node_->entry.second };
			    }
			    KeyType key;
			    DataType data;
			    return { key, data };
                    }				
                    /**
                     * class  const_generic_iterator
                     * @fn     operator== 
                     * @brief  boolean equal operator 
                     * @return bool indicates whether or not the given two instances are equal 
                    */ 
                    template <typename iter_type>
                    bool operator==(const const_generic_iterator<iter_type>& rhs) {
                            return this->_node_ == rhs._node_;
                    }
                    /**
                     * class  const_generic_iterator
                     * @fn     operator!= 
                     * @brief  boolean non-equal operator 
                     * @return bool indicates whether or not the given two instances are equal 
                    */ 
                    template <typename iter_type>
                    bool operator!=(const const_generic_iterator<iter_type>& rhs) {
                            return !((*this) == rhs);
                    }
	    };
            typedef generic_iterator<inorder_iterator_traits> inorder_iterator;
            typedef generic_iterator<preorder_iterator_traits> preorder_iterator;
            typedef generic_iterator<postorder_iterator_traits> postorder_iterator; 
            typedef const_generic_iterator<inorder_iterator_traits> const_inorder_iterator;
            typedef const_generic_iterator<preorder_iterator_traits> const_preorder_iterator;
            typedef const_generic_iterator<postorder_iterator_traits> const_postorder_iterator;
            /**
             * class  map
             * @fn     begin()
             * @brief  Returns an iterator to the starting element of the map 
             * @return generic_iterator<void> which is converting to the concreate iterator type(inorder_iterator, preorder_iterator, postorder_iterator)
            */ 
            generic_iterator<default_type> begin() {
                generic_iterator<default_type> git(this);
                return git;
            }
            /**
             * class  map
             * @fn     end()
             * @brief  Returns an iterator to the ending element of the map 
             * @return generic_iterator<void> which is converting to the concreate iterator type(inorder_iterator, preorder_iterator, postorder_iterator)
            */ 
            generic_iterator<default_type> end() {
                generic_iterator<default_type> git(nullptr);
                return git;
            }
            /**
             * class  map
             * @fn     cbegin()
             * @brief  Returns a const iterator to the starting element of the map 
             * @return const_generic_iterator<void> which is converting to the concreate iterator type(const_inorder_iterator, const_preorder_iterator, const_postorder_iterator)
            */ 
            const const_generic_iterator<default_type> cbegin() {
                    const const_generic_iterator<default_type> git(this);
                    return git;
            }
            /**
             * class  map
             * @fn     cend()
             * @brief  Returns a const iterator to the ending element of the map 
             * @return const_generic_iterator<void> which is converting to the concreate iterator type(const_inorder_iterator, const_preorder_iterator, const_postorder_iterator)
            */ 
            const const_generic_iterator<default_type> cend() {
                    const const_generic_iterator<default_type> git(nullptr);
                    return git;
            }
            /**
             * class  map
             * @fn     cfind()
             * @brief  Finds an element by the given key. 
             * @return generic_iterator<void> which is converting to the concreate iterator type(inorder_iterator, preorder_iterator, postorder_iterator)
            */ 
            generic_iterator<default_type> find(const KeyType& key) {
                    typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node = find_helper(root, key);
                    generic_iterator<default_type> git(this, node);
                    return git;
            }
            /**
             * class  map
             * @fn     cfind()
             * @brief  Finds an element by the given key. 
             * @return const_generic_iterator<void> which is converting to the concreate iterator type(inorder_iterator, preorder_iterator, postorder_iterator)
            */ 
            generic_iterator<default_type> cfind(const KeyType& key) {
                    typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node = find_helper(root, key);
                    generic_iterator<default_type> git(this, node);
                    return git;
            }
            /**
             * class  map
             * @fn     inorder_end()
             * @brief  Returns the last valid element in the inorder traversal. 
             * @return inorder_iterator to the last valid element in map
            */ 
            inorder_iterator inorder_end() {
                    typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node = inorder_end_helper();
                    inorder_iterator it(this, node);
                    return it;
            }
            /**
             * class  map
             * @fn     preorder_end()
             * @brief  Returns the last valid element in the preorder traversal. 
             * @return preorder_iterator to the last valid element in map
            */ 
            preorder_iterator preorder_end() {
                    typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node = preorder_end_helper();
                    preorder_iterator pit(this, node);
                    return pit;
            }
            /**
             * class  map
             * @fn     postorder_end()
             * @brief  Returns the last valid element in the postorder traversal. 
             * @return postorder_iterator to the last valid element in map
            */ 
            postorder_iterator postorder_end() {
                    typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node = postorder_end_helper();
                    postorder_iterator pit(this, node);
                    return pit;
            }
            /**
             * class  map
             * @fn     inorder_start()
             * @brief  Returns the first valid element in the inorder traversal. 
             * @return inorder_iterator to the first valid element in map
            */ 
            inorder_iterator inorder_start() {
                    typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node = inorder_start_helper();
                    inorder_iterator it(this, node);
                    return it;
            }
            /**
             * class  map
             * @fn     preorder_start()
             * @brief  Returns the first valid element in the preorder traversal. 
             * @return preorder_iterator to the first valid element in map
            */ 
            preorder_iterator preorder_start() {
                    typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node = preorder_start_helper();
                    preorder_iterator pit(this, node);
                    return pit;
            }
            /**
             * class  map
             * @fn     postorder_start()
             * @brief  Returns the first valid element in the postorder traversal. 
             * @return postorder_iterator to the first valid element in map
            */ 
            postorder_iterator postorder_start() {
                    typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node = postorder_start_helper();
                    postorder_iterator pit(this, node);
                    return pit;
            }
        private:
            size_t current_size;
            map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* root;				
			template <typename> friend struct generic_iterator_traits;
			template <typename, typename> friend class generic_iterator;
			template <typename> friend struct const_generic_iterator_traits;
			template <typename, typename> friend class const_generic_iterator;
    };

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
    typename AllocatorType>
    inline int map<KeyType, DataType, comparator, CONT, AllocatorType>::height(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node) {
        if(!node) {
            return 0;
        }	
        int left = height(node->left.get());
        int right =  height(node->right.get());
        return std::max(left, right) + 1;
    }
    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
    typename AllocatorType>
    inline const size_t map<KeyType, DataType, comparator, CONT, AllocatorType>::max_height() {
        return height(root);
    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* map<KeyType, DataType, comparator, CONT, AllocatorType>::get_min(const typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node) {
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* temp = node->right.get();
        while(temp->left) {
            temp = temp->left.get();
        }
        return temp;
    }
    
    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* map<KeyType, DataType, comparator, CONT, AllocatorType>::get_max(const typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node) {
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* temp = node->left.get();
        while(temp->right) {
            temp = temp->right.get();
        }
        return temp;
    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline void map<KeyType, DataType, comparator, CONT, AllocatorType>::remove(const KeyType& key) {
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node = find(key, nullptr);		
        if(!node) {		
            return;
        }
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* successor(nullptr);
        if(!node->left) {
                typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* nparent = node->parent;
                if(!node->right.get()){
                        if(node->parent && node == node->parent->right.get()) {
                                node->parent->right.reset();
                                --current_size;
                        } else if(node->parent && node == node->parent->left.get()) {
                                node->parent->left.reset();
                                --current_size;
                        } else {
                                if(root) {
                                        --current_size;
                                        alloc.destroy(root);
                                        alloc.deallocate(root, 1);
                                        root = nullptr;
                                }
                                return;
                        }
                } else {
                        transplant(node, node->right.get());
                        --current_size;
                        alloc.destroy(node);
                        alloc.deallocate(node, 1);
                }
                if(nparent) {
                        check_balance(nparent);
                }
        } else if(!node->right) {
                typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* nparent = node->parent;
                transplant(node, node->left.get());	
                alloc.destroy(node);
                alloc.deallocate(node, 1);
                --current_size;
                if(nparent) {
                        check_balance(nparent);
                }
        } else {
                successor = inorder_successor(node);
                if(successor->parent != node) {
                        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* tt = successor->right.release();
                        transplant(successor, tt);
                        check_balance(successor->parent);
                        successor->right.reset(node->right.release());
                        if(successor->right) {
                                successor->right->parent = successor;
                        }
                }
                typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* tt = nullptr;
                transplant(node, successor);
                successor->left.reset(node->left.release());		
                if(successor->left.get()) {
                        successor->left->parent = successor;
                }
                successor->parent = node->parent;
                if(node->parent && node == node->parent->right.get()) {
                        node->parent->right.reset(successor);
                } else if(node->parent && node == node->parent->left.get()) {
                        node->parent->left.reset(successor);
                }
                alloc.destroy(node);
                alloc.deallocate(node, 1);
                --current_size;
                check_balance(successor);		
        }
    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* map<KeyType, DataType, comparator, CONT, AllocatorType>::find_helper(const typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* parent_node, const KeyType key) {
        if(!parent_node || key == parent_node->entry.first) {
            return const_cast<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node*>(parent_node);
        }
        if(!(comparator<KeyType>()(key, parent_node->entry.first))) {
            return find_helper(parent_node->right.get(), key);
        } else if((comparator<KeyType>()(key, parent_node->entry.first))) {
            return find_helper(parent_node->left.get(), key);
        }
        return nullptr;
    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* map<KeyType, DataType, comparator, CONT, AllocatorType>::find(const KeyType& key, void*) {
        return find_helper(root, key);
    }
	
    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline void map<KeyType, DataType, comparator, CONT, AllocatorType>::destroy() {
        alloc.destroy(root);
        alloc.deallocate(root, 1);
    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline void map<KeyType, DataType, comparator, CONT, AllocatorType>::transplant(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* second_node) 
    {
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* pp = nullptr;
        if(second_node == node->right.get()) {
            second_node = node->right.release();
        } else if(second_node == node->left.get()) {
            second_node = node->left.release();
        }
        if(!node->parent) {
			if (second_node) {
				second_node->parent = nullptr;
			}
            root = second_node;
        }	
        if(node->parent && node->parent->right.get() == node) {
            if (second_node) {
                typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* tt = node->parent->right.release();
                second_node->parent = node->parent;
                node->parent->right.reset(second_node);
            } else {
                node->parent->right.release();
            }
        } else if(node->parent && node->parent->left.get() == node) { 
            if (second_node) {
                typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* tt = node->parent->left.release();
                second_node->parent = node->parent;
                node->parent->left.reset(second_node);
            } else {
                node->parent->left.release();
            }
        }	
        if(node->parent && second_node) {
            second_node->parent = node->parent;
        }
    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* map<KeyType, DataType, comparator, CONT, AllocatorType>::inorder_successor(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node) {
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* temp = node;
        if(temp->right) {
            return get_min(temp);
        }
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* parent = temp->parent;
        while(parent && temp == parent->right.get()) {
            temp = parent;
            parent = parent->parent;
        }
        return parent;
    }
            
    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* map<KeyType, DataType, comparator, CONT, AllocatorType>::postorder_successor(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node) {
        if(!node || !node->parent) {
            return nullptr;
        }
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* temp = node->parent;
        if(!temp->right || node == temp->right.get()) {
            return node->parent;
        } else {
            temp = temp->right.get();
            while(temp->left || temp->right) {
                if(temp->left) {
                    temp = temp->left.get();
                } else if(temp->right) {
                    temp = temp->right.get();
                }
            }
        }
        return temp;
    }
            
    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* map<KeyType, DataType, comparator, CONT, AllocatorType>::preorder_successor(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node) {
        if(!node) {
            return nullptr;
        }
        if(node->left.get()) {
            return node->left.get();
        }
        if(node->right.get()) {
            return node->right.get();
        }
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* temp = node;
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* parent = temp->parent;
        while(parent && (temp == parent->right.get()|| !parent->right)) {
            temp = temp->parent;
            parent = parent->parent;
        }
        if(!parent) {
            return nullptr;
        }
        return parent->right.get();
    }
    
    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* map<KeyType, DataType, comparator, CONT, AllocatorType>::inorder_predecessor(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node) {
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* temp = node;
        if(temp->left) {
            return get_max(temp);
        }
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* parent = temp->parent;
        while(parent && temp == parent->left.get()) {
            temp = parent;
            parent = parent->parent;
        }
        return parent;
    }
            
    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* map<KeyType, DataType, comparator, CONT, AllocatorType>::postorder_predecessor(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node) {
        if(!node) {
            return nullptr;
        }
        if(node->right) {
            return node->right.get();
        }
        if(!node->parent) {
            return nullptr;
        }
        if (node == node->parent->left) {
                return node->parent->right.get();
        }
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* temp = node;
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* parent = temp->parent;
        while(parent && temp == parent->left) {
            temp = parent;
            parent = parent->parent;
        }
        if(!parent) {
            return nullptr;
        }
        return parent->left.get();
    }
            
    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* map<KeyType, DataType, comparator, CONT, AllocatorType>::preorder_predecessor(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node) {
        if(!node || node == root) {
            return nullptr;
        }
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* parent = node->parent;
        if(node == parent->left || !parent->left) {
            return parent;
        }
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* temp = parent->left;
        while(parent->right) {
            temp = temp->right;
        }
        return temp.get();
    }
    
    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* map<KeyType, DataType, comparator, CONT, AllocatorType>::inorder_end_helper() {
        if(!root) {
            return nullptr;
        }
        if(!root->right) {
            return root;
        }
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* temp = root;
        while(temp->right) {
            temp = temp->right.get();
        }
        return temp;
    }
    
    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* map<KeyType, DataType, comparator, CONT, AllocatorType>::inorder_start_helper() {
        if(!root) {
            return nullptr;
        }
        if(!root->left) {
            return root;
        }
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* temp = root;
        while(temp->left) {
            temp = temp->left.get();
        }
        return temp;
    }
            
    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* map<KeyType, DataType, comparator, CONT, AllocatorType>::preorder_end_helper() {
        if(!root) {
            return nullptr;
        }
        if(root->right) {
            typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* temp = root->right.get();
            while(temp->right) {
                temp = temp->right.get();
            }
            if(temp->left) {
                return temp->left.get();
            } 
            return temp;
        } else if(root->left) {
            typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* temp = root->left.get();
            while(temp->right) {
                temp = temp->right.get();
            }
            return temp;
        } 
        return root;
    }
    
    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* map<KeyType, DataType, comparator, CONT, AllocatorType>::preorder_start_helper() {
        return root;
    }
    
    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* map<KeyType, DataType, comparator, CONT, AllocatorType>::postorder_end_helper() {
        return root;
    }
    
    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* map<KeyType, DataType, comparator, CONT, AllocatorType>::postorder_start_helper() {
        if(!root) {
            return nullptr;
        }
        if(!root->left && !root->right) {
            return root;
        }
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* temp = root;
        while(temp->left || temp->right) {
            if(temp->left) {
                temp = temp->left.get();
            } else if(temp->right) {
                temp = temp->right.get();
            }
        }
        return temp;
    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node> map<KeyType, DataType, comparator, CONT, AllocatorType>::left_rotate(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node) {    
        std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node> temp = std::move(node->right);
        node->right = std::move(temp->left);
        temp->left.reset(node);
        if(node->right.get()) {
            node->right->parent = node;
        }
        temp->parent = node->parent;
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* temp_raw = temp.release();
        if(node->parent) {
            if(node == node->parent->left.get()) {			
                node->parent->left.release();
                node->parent->left.reset(temp_raw);
            } else if(node == node->parent->right.get()) {			
                node->parent->right.release();
                node->parent->right.reset(temp_raw);
            }
        }    
        node->parent = temp_raw;    
        return std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node>(temp_raw);
    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node> map<KeyType, DataType, comparator, CONT, AllocatorType>::right_rotate(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node) {    
        std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node> temp = std::move(node->left);
        node->left = std::move(temp->right);
        temp->right.reset(node);
        if(node->left.get()) {
            node->left->parent = node;
        }
        temp->parent = node->parent;
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* temp_raw = temp.release();
        if(node->parent) {
            if(node == node->parent->left.get()) {					
                node->parent->left.release();
                node->parent->left.reset(temp_raw);
            } else if(node == node->parent->right.get()) {			
                node->parent->right.release();
                node->parent->right.reset(temp_raw);
            }
        }    
        node->parent = temp_raw;    
        return std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node>(temp_raw);	
    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node> map<KeyType, DataType, comparator, CONT, AllocatorType>::left_right_rotate(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node) {
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* left = node->left.release();
        node->left = std::move(left_rotate(left));
        return right_rotate(node);

    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node> map<KeyType, DataType, comparator, CONT, AllocatorType>::right_left_rotate(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node) {
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* right = node->right.release();
        node->right = std::move(right_rotate(right));
        return left_rotate(node);
    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline void map<KeyType, DataType, comparator, CONT, AllocatorType>::insert_helper(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* parent, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node*& node) {
        if(!(comparator<KeyType>()(node->entry.first, parent->entry.first)) && !(comparator<KeyType>()(parent->entry.first, node->entry.first))) {
            alloc.destroy(node);
            alloc.deallocate(node, 1);
            node = nullptr;
            return;
        }
        if(node) {
            if(!(comparator<KeyType>()(node->entry.first, parent->entry.first))) {
                if(!parent->right.get()) {
                    parent->right.reset(node);
                    node->parent = parent;
                    ++current_size;
                } else {
                    insert_helper(parent->right.get(), node);
                }
            } else if(comparator<KeyType>()(node->entry.first, parent->entry.first)) {
                if(!parent->left.get()) {
                    parent->left.reset(node);
                    node->parent = parent;
                    ++current_size;
                } else {
                    insert_helper(parent->left.get(), node);
                }

            } 
            if(node) {
                check_balance(node);
            }
        }
        return;
    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline void map<KeyType, DataType, comparator, CONT, AllocatorType>::insert(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node) {
        if(!root) {
            root = node;
            return;
        }
        insert_helper(root, node);
    }
    
    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline void map<KeyType, DataType, comparator, CONT, AllocatorType>::insert(const KeyType& key) {
        if(!root) {
            root = _node_allocator_traits::allocate(alloc, 1);
            alloc.construct(root, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node(key));
            ++current_size;
            return;
        } 
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node = _node_allocator_traits::allocate(alloc, 1);
        alloc.construct(node, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node(key));
        insert_helper(root, node); 
    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline void map<KeyType, DataType, comparator, CONT, AllocatorType>::insert(const KeyType& key, const DataType& data) {
        if(!root) {
            root = _node_allocator_traits::allocate(alloc, 1);
            alloc.construct(root, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node(key, data));
            return;
        } 
        typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node = _node_allocator_traits::allocate(alloc, 1);
        alloc.construct(node, typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node(key, data));
        insert_helper(root, node); 
    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline void map<KeyType, DataType, comparator, CONT, AllocatorType>::check_balance(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node) {
        int left = height(node->left.get());
        int right = height(node->right.get());
        if(left - right > 1 || left - right < -1) {
            std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node> uptr = std::move(rebalance(node));
            node = uptr.release();
        } 
        if(!node->parent) {
            return;
        }
        check_balance(node->parent);
    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node> map<KeyType, DataType, comparator, CONT, AllocatorType>::rebalance(typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* node) {
        int left = height(node->left.get());
        int right = height(node->right.get());
        std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node> uptr = std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node>();
        if(left - right > 1) {
            if(height(node->left->left.get()) >= height(node->left->right.get())) {
                uptr = std::move(right_rotate(node));
            } else {
                uptr = std::move(left_right_rotate(node));
            }

        }
        left = height(node->left.get());
        right = height(node->right.get());
        if(left - right < -1) {
            if(height(node->right->right.get()) >= height(node->right->left.get())) {
                uptr = std::move(left_rotate(node));            
            } else {
                uptr = std::move(right_left_rotate(node));
            }
        }
        if(!uptr->parent) {
            root = uptr.release();
            return std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node>(root);
        }
        return uptr;
    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline void map<KeyType, DataType, comparator, CONT, AllocatorType>::traverse_inorder(std::vector<KeyType>& out) {
        if(root) {
            std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node> root_ptr(root);
            traverse_inorder_helper(root_ptr, out);
            root = root_ptr.release();
        }
    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline void map<KeyType, DataType, comparator, CONT, AllocatorType>::traverse_preorder(std::vector<KeyType>& out) {
        if(root) {
            std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node> root_ptr(root);
            traverse_preorder_helper(root_ptr, out);
            root = root_ptr.release();
        }
    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline void map<KeyType, DataType, comparator, CONT, AllocatorType>::traverse_postorder(std::vector<KeyType>& out) {
        if(root) {
            std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node> root_ptr(root);
            traverse_postorder_helper(root_ptr, out);
            root = root_ptr.release();
        }
    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline void map<KeyType, DataType, comparator, CONT, AllocatorType>::traverse_inorder_helper(std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node>& node, 
            std::vector<KeyType>& out) {
        if(!node) {
            return;
        }
        traverse_inorder_helper(node->left, out);
        out.push_back(node->entry.first);
        traverse_inorder_helper(node->right, out);
    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline void map<KeyType, DataType, comparator, CONT, AllocatorType>::traverse_preorder_helper(std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node>& node, 
            std::vector<KeyType>& out) {
        if(!node) {
            return;
        }
        out.push_back(node->entry.first);
        if(node->left) {
                typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* tnd = node->left.get();
        }
        if(node->right) {
                typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* tnd = node->right.get();
        }
        traverse_preorder_helper(node->left, out);
        traverse_preorder_helper(node->right, out);
    }

    template <typename KeyType, 
              typename DataType, 
              template <typename> class comparator,
              template <typename T, typename ALLOC = std::allocator<T> > class CONT,
              typename AllocatorType>
    inline void map<KeyType, DataType, comparator, CONT, AllocatorType>::traverse_postorder_helper(std::unique_ptr<typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node>& node, 
            std::vector<KeyType>& out) {
        if(!node) {
            return;
        }
        if(node->left) {
                typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* tnd = node->left.get();
        }
        if(node->right) {
                typename map<KeyType, DataType, comparator, CONT, AllocatorType>::Node* tnd = node->right.get();
        }
        traverse_postorder_helper(node->left, out);
        traverse_postorder_helper(node->right, out);
        out.push_back(node->entry.first);
    }
}
