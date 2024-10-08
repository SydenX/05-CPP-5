
#include "Form.hpp"

//Constructor
Form::Form(std::string name): _name(name), _isSigned(0), _gradeToSign(150), _gradeToExecute(150) {

}

Form::Form(std::string name, int gradeToExecute, int gradeToSign): _name(name), _isSigned(0), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
	if (gradeToExecute > 150 || gradeToSign > 150)
		throw Form::GradeTooLowException();
	else if (gradeToExecute < 1 || gradeToSign < 1)
		throw Form::GradeTooHighException();
}

//Destructor
Form::~Form() {
}

//Copy-Constructor
Form::Form(Form const &form): _name(form.getName()), _isSigned(0),  _gradeToSign(form.getSignatureGrade()), _gradeToExecute(form.getExecutionGrade()) {
	*this = form;
}

//Copy-Assignment Operator Overload
Form&	Form::operator=(Form const &form) {
	if (this == &form)
		return *this;
	this->_isSigned = form.isSigned();
	return *this;
}

void Form::beSigned(Bureaucrat const &executor){
	if (executor.getGrade() <= this->getSignatureGrade()){
		if (this->_isSigned == 1)
			std::cout << executor.getName() << " couldn't sign " << this->getName() << " because the form is already signed." << std::endl;
		else {
			this->_isSigned = 1;
			std::cout << executor.getName() << " signed " << this->getName() << std::endl;
		}
	} else {
		throw(Form::GradeTooLowException());
	}
}

std::string const &Form::getName() const {
	return this->_name;
}

bool Form::isSigned() const {
	return this->_isSigned;
}

int Form::getExecutionGrade() const {
	return this->_gradeToExecute;
}

int Form::getSignatureGrade() const {
	return this->_gradeToSign;
}

const char *Form::GradeTooHighException::what() const throw() {
	return ("Grade too high to execute or sign.");
}

const char *Form::GradeTooLowException::what() const throw() {
	return ("Grade too low to execute or sign.");
}

std::ostream &operator<<(std::ostream &output, const Form &form){
	output << form.getName() << "\nisSigned: " << form.isSigned() << "\nGrade required to sign: " << form.getSignatureGrade() << "\nGrade required to execute: " << form.getExecutionGrade() << std::endl;
	return output;
}