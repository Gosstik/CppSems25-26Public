// Same as combiners in futures.

// ! Range adapters make transition from ranges::view to ranges::view.

// filter_view
// transform_view
// take_view / take_while_view
// drop_view / drop_while_view
// join_view
// split_view
// reverse_view

//// Range adapter objects

// std::ranges::filter_view(range, predicate)
// vi::filter(range, predicate) // nibloid
// vi::filter(predicate)(range) // nibloid
// range | vi::filter(predicate) // pipe from bash
