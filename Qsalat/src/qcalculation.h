#ifndef __CALCULATION_H__
#define __CALCULATION_H__

#include <QtGui>
#include <QString>
#include "ui_calculation.h"

class Qcalculation : public QDialog, public Ui::Calculation
{
Q_OBJECT
public:
	Qcalculation( QWidget * parent = 0, Qt::WFlags f = 0 );	
	
public slots:	

protected:
	void closeEvent(QCloseEvent *);
	
signals:	
	
private:
	 void setUI();
	 void setMethods();
};

#endif // __CALCULATION_H__