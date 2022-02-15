#include <iostream>

import Domain.Auth;

int main()
{
	std::cout << domain::auth::GenerateRandomCode() << '\t'
		<< domain::auth::GenerateRandomCode() << '\n';
}
