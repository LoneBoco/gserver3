export module graal.core:concepts;

export
{

template <class T>
concept has_empty_function =
	requires(T a) {
		a.empty();
	};

}
