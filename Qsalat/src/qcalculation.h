#ifndef __CALCULATION_H__
#define __CALCULATION_H__

#include <QtGui>
#include <QString>
#include "ui_calculation.h"
#include "domparser.h"
#include "qpray.h"

class Qcalculation : public QDialog, public Ui::Calculation
{
Q_OBJECT
public:
	Qcalculation( QWidget * parent = 0, Qt::WFlags f = 0 );	
	void init(int);
	
protected:
	void closeEvent(QCloseEvent *);
	
private slots:	
	void save();
	void cancel();
	void apply();
	
private:
	 void setUI();	 
	 void setActions();
	 DomParser parser;
	 QString file;
	 QStringList list;		
	 QString path;
	 Qpray *prayers;
	 QDate date;
	 int calcMethod;
	 int asrMethod;
	 int duhrMinutes;
	 int calcTime(QString,QString);
	 int getDuhrMinutes();
	 int setDuhrMinutes();
};

#endif // __CALCULATION_H__
