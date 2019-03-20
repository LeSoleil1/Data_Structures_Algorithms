
		// Mutators

		void swap( Cyclic_double_list & );
		Cyclic_double_list &operator=( Cyclic_double_list const & );

		void push_front( Type const & );
		void push_back( Type const & );

		Type pop_front();
		Type pop_back();

		int erase( Type const & );

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Cyclic_double_list<T> const & );
};

#endif
