/********************************************************
* Class:            ksErrorReport
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksErrorReport.h
*
*   Overview:
*       Class for reporting errors in a system
*       independent way.
*
********************************************************/

#ifndef KS_ERROR_REPORT_H
#define KS_ERROR_REPORT_H

#include "defines.h"
#include <vector>

#ifdef DESKTOP_BUILD
#include <iostream>
#include <string>
#endif

class ksErrorReport
{
	public:
		//                       Constructors
		inline ksErrorReport() { }
		inline ksErrorReport(std::string error)
		{
			m_errors.push_back(error);
		}

		//                       Methods
		inline void              reportNewError(std::string error)
		{
			m_errors.push_back("ERROR: " + error);

#ifdef DESKTOP_BUILD
			std::cout << error << std::endl;
#endif
		}
		
		//                       Accessor methods
		inline std::string       getErrorReport()
		{
			std::string report;

			for (unsigned int count = 0; count < m_errors.size(); ++count)
			{
				report += m_errors[count];
				report += '\n';
			}

			return report;
		}

	private:
		//                       Data members
		std::vector<std::string> m_errors;
};

#endif