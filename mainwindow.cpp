#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEditor);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    filePath.clear();
    ui->textEditor->setText("");
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileNameStr = QFileDialog::getOpenFileName(this, "Open a File");

    QFile file(fileNameStr);
    filePath = fileNameStr;

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", file.errorString());
        return;
    }

    QTextStream in(&file);
    ui->textEditor->setText(in.readAll());

    file.close();
}


void MainWindow::on_actionSave_triggered()
{
    QString fileNameStr = QFileDialog::getSaveFileName(this, "Save a File");

    if (fileNameStr.isEmpty()) return;

    QFile file(fileNameStr);
    filePath = fileNameStr;

    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", file.errorString());
        return;
    }

    QTextStream out(&file);
    out << ui->textEditor->toPlainText();

    file.close();
}


void MainWindow::on_actionSave_As_triggered()
{
    QString fileNameStr = QFileDialog::getSaveFileName(this, "Save a File");

    if (fileNameStr.isEmpty()) return;

    QFile file(fileNameStr);
    filePath = fileNameStr;

    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", file.errorString());
        return;
    }

    QTextStream out(&file);
    out << ui->textEditor->toPlainText();

    file.close();
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog qDialog(&printer, this);

    if (qDialog.exec() == QDialog::Rejected) {
        QMessageBox::warning(this, "Error", "Could not access Printer");
        return;
    }

    ui->textEditor->print(&printer);
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEditor->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEditor->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEditor->paste();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEditor->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEditor->redo();
}

