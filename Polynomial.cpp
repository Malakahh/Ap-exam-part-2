#include "Polynomial.h"

Polynomial::Polynomial(): Polynomial{0, 0}{}

Polynomial::Polynomial(const Polynomial& p)
{
	this->coefficients = std::vector<int>(p.coefficients);
}

Polynomial::Polynomial(const int value, const unsigned int exponent)
{
	this->SetCoefficient(value, exponent);
}

void Polynomial::SetCoefficient(const int value, const unsigned int exponent)
{
	if (exponent < this->coefficients.size())
	{
		this->coefficients[exponent] = value;
	}
	else if (exponent >= this->coefficients.size())
	{
		for (unsigned int i = coefficients.size(); i < exponent + 1; i++)
		{
			if (i < exponent)
			{
				this->coefficients.push_back(0);
			}
			else
			{
				this->coefficients.push_back(value);
			}
		}
	}
}

const int Polynomial::GetCoefficient(const unsigned int exponent) const
{
	if (exponent >= this->coefficients.size())
	{
		throw std::out_of_range("Index out of bounds");
	}

	return this->coefficients[exponent];
}

const int Polynomial::GetHighestCoefficient() const
{
	return this->coefficients.size() - 1;
}

void Polynomial::Scale(const int scalar)
{
	for (auto i = 0; i <= this->GetHighestCoefficient(); i++)
	{
		this->SetCoefficient(this->GetCoefficient(i) * scalar, i);
	}
}

void Polynomial::AddRoot(const int root)
{
	const auto start = this->GetHighestCoefficient();
	for (auto i = start; i >= 0; i--)
	{
		//Move value to higher exponent
		if (i == this->GetHighestCoefficient())
		{
			//Higher exponent does not yet exist
			this->SetCoefficient(this->GetCoefficient(i), i + 1);
		}
		else
		{
			//Higher expoent exists, so add to its value
			this->SetCoefficient(this->GetCoefficient(i) + this->GetCoefficient(i + 1), i + 1);
		}

		//Calculate current exponent value
		this->SetCoefficient(this->GetCoefficient(i) * root * -1, i);
	}
}

double Polynomial::ValueAt(const double x)
{
	double res = 0;

	for (auto i = 0; i <= this->GetHighestCoefficient(); i++)
	{
		res += this->GetCoefficient(i) * std::pow(x, i);
	}

	return res;
}

Polynomial Polynomial::CalculateDerivative()
{
	Polynomial p(*this);

	for (auto i = 0; i < p.GetHighestCoefficient(); i++)
	{
		p.SetCoefficient(p.GetCoefficient(i + 1) * (i + 1), i);
	}

	//Erase last exponent
	p.coefficients.erase(p.coefficients.end() - 1);

	return p;
}

double Polynomial::IntegralPart(const int n)
{
	auto res = 0.;

	for (auto i = 0; i <= this->GetHighestCoefficient(); i++)
	{
		res += this->GetCoefficient(i) * std::pow(n, i + 1) / (i + 1);
	}

	return res;
}

double Polynomial::CalculateIntegral(const int a, const int b)
{
	return this->IntegralPart(b) - this->IntegralPart(a);
}

std::ostream& operator<<(std::ostream& s, const Polynomial& p)
{
	s << "P(x) = ";

	for (int i = p.coefficients.size() - 1; i >= 0; i--)
	{
		s << p.GetCoefficient(i);
		if (i > 0)
		{
			if (i == 1)
			{
				s << "x + ";
			}
			else
			{
				s << "x^" << i << " + ";		
			}
		}
	}

	return s;
}