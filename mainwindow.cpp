#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName= QFileDialog::getOpenFileName(this,"Open the File");
    QFile file(fileName);
       currentFile = fileName;
       if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
           QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
           return;
       }
       setWindowTitle(fileName);
       QTextStream in(&file);
       QString text = in.readAll();
       ui->textEdit->setText(text);
       file.close();

}


void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
       QFile file(fileName);

       if (!file.open(QFile::WriteOnly | QFile::Text)) {
           QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
           return;
       }
       currentFile = fileName;
       setWindowTitle(fileName);
       QTextStream out(&file);
       QString text = ui->textEdit->toPlainText();
       out << text;
       file.close();
}


void MainWindow::on_actionSave_triggered()
{
    QString fileName;
       // If we don't have a filename from before, get one.
       if (currentFile.isEmpty()) {
           fileName = QFileDialog::getSaveFileName(this, "Save");
           currentFile = fileName;
       } else {
           fileName = currentFile;
       }
       QFile file(fileName);
       if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
           QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
           return;
       }
       setWindowTitle(fileName);
       QTextStream out(&file);
       QString text = ui->textEdit->toPlainText();
       out << text;
       file.close();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionExit_triggered()
{
      QCoreApplication::quit();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionUndo_triggered()
{
     ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
     ui->textEdit->redo();
}


void MainWindow::on_actionBold_triggered()
{
    ui->textEdit->setFontWeight(100);
}


void MainWindow::on_actionItalics_triggered()
{
    ui->textEdit->setFontItalic(true);
}


void MainWindow::on_actionUnderline_triggered()
{
    ui->textEdit->setFontUnderline(true);
}


void MainWindow::on_actionFont_Size_triggered()
{
    bool fontSelected;
       QFont font = QFontDialog::getFont(&fontSelected, this);
       if (fontSelected)
           ui->textEdit->setFont(font);
}


void MainWindow::on_actionSuperScript_triggered()
{
  ui->textEdit->setText("x<sup>2</sup>");

}

