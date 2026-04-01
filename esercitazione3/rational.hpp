#include <iostream>
#include <concepts>
#include <numeric>

template<typename I> requires std::signed_integral<I>
class rational
{
	I num_;
	I den_;
	
	void semplifica() {
		// Normalizza i casi limite (+/-Inf e Nan):
		// +Inf = 1/0, -Inf = -1/0, NaN = 0/0
		// Semplifica ai minimi termini i casi normali
		// Se il denominatore è negativo cambia i segni
		
		if (den_ == 0) {
			if (num_ > 0) {
				num_ = I{1};  
			} else if (num_ < 0) {
				num_ = I{-1}; 
			} else {
				num_ = I{0};  
			}
			return;
		}
		
		I mcd = std::gcd(num_, den_);
		num_ /= mcd;
		den_ /= mcd;
		
		if (den_ < 0) {
			num_ = -num_;
			den_ = -den_;
		}
		return;
	}
	
public:
	rational()
		: num_(I{0}), den_(I{1})
	{}
	
	rational(const I& numer,const I& denom)
		: num_(numer), den_(denom)
	{
		semplifica();
	}
	
	I num() const { return num_; }
	I den() const { return den_; }
	
	bool is_nan() const {
		return (den_ == 0 && num_ == 0);
	}

	bool is_inf() const {
		return (den_ == 0 && num_ != 0);
	}
	
	rational& operator+=(const rational& other) {
		if (is_nan() || other.is_nan()) {
			num_ = I{0};
			den_ = I{0};
			return *this;
		}
		
		if (is_inf() && other.is_inf()) {
			// (+Inf) + (-Inf) = NaN 
			if (num_*other.num_ < 0) {
				num_ = I{0};
				den_ = I{0};
				return *this;
			}
			else {
				return *this;
			}
		}
				
		if (is_inf()) {
			return *this;
		}
		
		if (other.is_inf()) {
			num_ = other.num_;
			den_ = other.den_;
			return *this;
		}
		
		I mcm = std::lcm(den_, other.den_);
		num_ = num_*(mcm/den_) + other.num_*(mcm/other.den_);
		den_ = mcm;
		
		semplifica();
		
		return *this;
	}	
	
	rational operator+(const rational& other) const {
		rational ret = *this;
		ret += other;
		return ret;		
	}
	
	rational& operator-=(const rational& other) {
		if (is_nan() || other.is_nan()) {
			num_ = I{0};
			den_ = I{0};
			return *this;
		}
		
		if (is_inf() && other.is_inf()) {
			// (+Inf) - (+Inf) = NaN 
			if (num_*other.num_ > 0) {
				num_ = I{0};
				den_ = I{0};
				return *this;
			}
			else {
				return *this;
			}
		}
		
		if (is_inf()) {
			return *this;
		}
		
		if (other.is_inf()) {
			num_ = -other.num_;
			den_ = other.den_;
			return *this;
		}
		
		I mcm = std::lcm(den_, other.den_);
		num_ = num_*(mcm/den_) - other.num_*(mcm/other.den_);
		den_ = mcm;
		
		semplifica();
		
		return *this;
	}	
		
	rational operator-(const rational& other) const {
		rational ret = *this;
		ret -= other;
		return ret;		
	}
	
	rational& operator*=(const rational& other) {
		if (is_nan() || other.is_nan()) {
			num_ = I{0};
			den_ = I{0};
			return *this;
		}
		
		if (is_inf() || other.is_inf()) {
			/* Inf*0 = NaN */
			if (num_*other.num_ == 0) {
				num_ = I{0};
				den_ = I{0};
			}
			else if (num_*other.num_ > 0) {
				num_ = I{1};
				den_ = I{0};
			}
			else {
				num_ = I{-1};
				den_ = I{0};
			}
			return *this;
		}
		
		num_ *= other.num_;
		den_ *= other.den_;
		semplifica();
		return *this;
	}
	
	rational operator*(const rational& other) const {
		rational ret = *this;
		ret *= other;
		return ret;
	}
	
	rational& operator/=(const rational& other) {
		if (is_nan() || other.is_nan()) {
			num_ = I{0};
			den_ = I{0};
			return *this;
		}
		
		if (is_inf() && other.is_inf()) {
			// Inf/Inf = NaN 
			num_ = I{0};
			den_ = I{0};
			return *this;
		}
		
		if (other.num_ == 0) {
			if (num_ == 0) {
				// 0/0 = NaN
				num_ = I{0};
				den_ = I{0};
			}
			else if (num_ > 0) {
				num_ = I{1};
				den_ = I{0};
			}
			else {
				num_ = I{-1};
				den_ = I{0};
			}
			return *this;
		}
		
		if (is_inf()) {
			if (other.num_ < 0) {
				num_ = -num_;
			}
			return *this;
		}
		
		if (other.is_inf()) {
			// x/Inf = 0
			num_ = I{0};
			den_ = I{1};
			return *this;
		}

		num_ *= other.den_;
		den_ *= other.num_;
		semplifica();
		return *this;
	}
	
	rational operator/(const rational& other) const {
		rational ret = *this;
		ret /= other;
		return ret;
	} 
	
};

template<typename I>
std::ostream&
operator<<(std::ostream& os, const rational<I>& q)
{
	if (q.is_nan()) {
		os << "NaN";
	}
	else if (q.is_inf()) {
		if (q.num() > 0) {
			os << "+Inf";
		}
		else {
			os << "-Inf";
		}
	}
	else if (q.num()==0) {
		os << "0";
	}
	else if (q.den()==1) { 
	os << q.num(); 
	}
	else {
		os << q.num() << "/" << q.den();
	}
	
	return os;
}
