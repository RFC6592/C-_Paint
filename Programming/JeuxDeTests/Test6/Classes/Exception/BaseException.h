#ifndef BASE_EXCEPTION_H
#define BASE_EXCEPTION_H


class BaseException
{
	protected:
		char pMsg[80];
		
	public:
		BaseException(void);
		BaseException(const char pMsg[80]); 
		virtual ~BaseException();
		BaseException(const BaseException &b);

		const char * getErreur(void) const;
		virtual void setErreur(const char pMsg[80]);
};

#endif
