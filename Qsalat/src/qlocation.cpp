#include "qlocation.h"
//
Qlocation::Qlocation( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
	setUI();
	manager = new QNetworkAccessManager(this);
	setActions();
	file = "data/qsalat.xml";
	parser.readFile(file);	
	bool ok;	
	latitude = parser.getElement(0,0).toFloat(&ok);
	longitude = parser.getElement(0,1).toFloat(&ok);
	country = parser.getElement(0,2);
	city = parser.getElement(0,3);
	timezone = parser.getElement(0,1).toInt(&ok);	
	loadCoordinates(longitude,latitude);
	latLineEdit->setText(QString::number(latitude));
    lngLineEdit->setText(QString::number(longitude));
    countryLineEdit->setText(country);
    cityLineEdit->setText(city);
    timezoneLineEdit->setText(QString::number(timezone));
}

void Qlocation::loadAddress(QString adr)
{
    QStringList scriptStr;    
    foreach( QPointF point, coordinates ) {
        latLineEdit->setText(QString::number(point.x()));
        lngLineEdit->setText(QString::number(point.y()));
    }   
   scriptStr << QString("http://www.skanderjabouzi.com/qpray/?adr=%1")                        
                             .arg(adr);
    
    QUrl url(scriptStr.join("\n"));
    webView->load(url);
    //update();    
}

void Qlocation::loadCoordinates(float lat, float lng)
{
    QStringList scriptStr;    
    //foreach( QPointF point, coordinates ) {
        //latLineEdit->setText(QString::number(point.x()));
        //lngLineEdit->setText(QString::number(point.y()));
    //}   
   scriptStr << QString("http://www.skanderjabouzi.com/qpray/?adr=0&lat=%1&lng=%2")                        
                             .arg(QString::number(lat))
                             .arg(QString::number(lng));
    
    QUrl url(scriptStr.join("\n"));
    webView->load(url);
    //update();    
}

void Qlocation::clearCoordinates()
{
    coordinates.clear();   
}

void Qlocation::showItem()
{
    //geoCode( locationLineEdit->text() );   
    applyButton->setEnabled(false);
    loadAddress( locationLineEdit->text() );  
    //emit(updateMap());    
}

void Qlocation::updateLatLng(){
	applyButton->setEnabled(true);
	QStringList scriptStr1,scriptStr2,scriptStr3,scriptStr4,scriptStr5; 
	scriptStr1 << "document.getElementById(\"lat\").value;";
	QVariant vres1 = webView->page()->mainFrame()->evaluateJavaScript( scriptStr1.join("\n") );
    QString sres1 = vres1.toString();
    
    scriptStr2 << "document.getElementById(\"lng\").value;";
	QVariant vres2 = webView->page()->mainFrame()->evaluateJavaScript( scriptStr2.join("\n") );
    QString sres2 = vres2.toString();
    
    scriptStr3 << "document.getElementById(\"country\").value;";
	QVariant vres3 = webView->page()->mainFrame()->evaluateJavaScript( scriptStr3.join("\n") );
    QString sres3 = vres3.toString();
    
    scriptStr4 << "document.getElementById(\"city\").value;";
	QVariant vres4 = webView->page()->mainFrame()->evaluateJavaScript( scriptStr4.join("\n") );
    QString sres4 = vres4.toString();
    
    scriptStr5 << "document.getElementById(\"timezone\").value;";
	QVariant vres5 = webView->page()->mainFrame()->evaluateJavaScript( scriptStr5.join("\n") );
    QString sres5 = vres5.toString();
    
    latLineEdit->setText(sres1);
    lngLineEdit->setText(sres2);
    countryLineEdit->setText(sres3);
    cityLineEdit->setText(sres4);
    timezoneLineEdit->setText(sres5);    
    //apply();   
}

void Qlocation::closeEvent(QCloseEvent *event)
{
	hide();
	event->ignore();
}

void Qlocation::setActions(){
	//connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
    //connect(this,SIGNAL(loadFinished(ok)),this,SLOT(updateLatLng()));
    //connect(this,SIGNAL(reloadMap()),this,SLOT(loadCoordinates()));
    connect(searchButton,SIGNAL(clicked()),this,SLOT(showItem()));  
    connect(applyButton,SIGNAL(clicked()),this,SLOT(updateLatLng()));
    connect(webView,SIGNAL(loadFinished ( bool )),this,SLOT(updateLatLng()));
    connect(this,SIGNAL(updateMap()),this,SLOT(updateLatLng())); 
}

void Qlocation::setUI(){
	setWindowIcon(QIcon("images/mecque.png"));
	okButton->setIcon(style()->standardIcon(QStyle::SP_DialogOkButton));
	applyButton->setIcon(style()->standardIcon(QStyle::SP_DialogApplyButton));
	cancelButton->setIcon(style()->standardIcon(QStyle::SP_DialogCancelButton));
}

void Qlocation::apply()
{
	parser.changeElement(latLineEdit->text(),0,0);
	parser.changeElement(lngLineEdit->text(),0,1);
	parser.saveData(file);
	DomParser::changed = true; 
}

void Qlocation::save()
{
	apply();
	close();
}

void Qlocation::cancel()
{
	close();
}
//
