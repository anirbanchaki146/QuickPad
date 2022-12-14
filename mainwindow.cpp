#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->editorTabs);

    int tabIndex = ui->editorTabs->addTab(new QTextEdit, "unsaved*");
    QWidget* tabWidget = ui->editorTabs->widget(tabIndex);
    tabWidget->setProperty("filePath", QString());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_editorTabs_tabCloseRequested(int index)
{
    auto reply = QMessageBox::question(
        this, "Save the file...",
        "You may have unsaved work. Would you like to save these changes?",
        QMessageBox::Save | QMessageBox::No | QMessageBox::Cancel
    );

    switch (reply) {
    case QMessageBox::Save:
        on_actionSave_triggered();
        break;

    case QMessageBox::No:
        break;

    default:
        return;
    }

    ui->editorTabs->removeTab(index);
}


void MainWindow::on_actionNew_triggered()
{
    int tabIndex = ui->editorTabs->addTab(new QTextEdit, "unsaved*");
    QWidget* tabWidget = ui->editorTabs->widget(tabIndex);
    tabWidget->setProperty("filePath", QString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(
        this, "Open a File"
    );

    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", file.errorString());
        return;
    }

    QTextStream in(&file);
    QTextEdit* textEdit = new QTextEdit;

    textEdit->setText(in.readAll());

    int tabIndex = ui->editorTabs->addTab(textEdit, filePath.section("/",-1,-1));
    ui->editorTabs->setCurrentIndex(tabIndex);

    QWidget* tabWidget = ui->editorTabs->widget(tabIndex);

    tabWidget->setProperty("filePath", filePath);

    file.close();
}


void MainWindow::on_actionSave_triggered()
{
    QWidget* currentTab = ui->editorTabs->currentWidget();

    if (currentTab == NULL) {
        QMessageBox::warning(this, "Warning", "No tab was selected");
        return;
    }

    QString filePath = currentTab->property("filePath").toString();

    if (filePath.isEmpty()) {
        QString filePath = QFileDialog::getSaveFileName(
            this, "Save the File", QString(),
            tr("Text Document (*.txt);; All files (*.*)"),
            new QString("Text Document (*.txt)")
        );

        if (filePath.isEmpty()) return;
    }

    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", file.errorString());
        return;
    }

    QTextStream out(&file);

    QTextEdit* currentTextEdit =
    static_cast<QTextEdit*>(currentTab);

    out << currentTextEdit->toPlainText();

    ui->editorTabs
    ->setTabText(
        ui->editorTabs->currentIndex(),
        filePath.section("/",-1,-1)
    );

    currentTab->setProperty("filePath", filePath);

    file.close();
}


void MainWindow::on_actionSave_As_triggered()
{
    QWidget* currentTab = ui->editorTabs->currentWidget();

    if (currentTab == NULL) {
        QMessageBox::warning(this, "Warning", "No tab was selected");
        return;
    }

    QTextEdit* currentTextEdit = static_cast<QTextEdit*>(currentTab);

    QString filePath = QFileDialog::getSaveFileName(
        this, "Save the File", QString(),
        tr("Text Document (*.txt);; All files (*.*)"),
        new QString("Text Document (*.txt)")
    );

    if (filePath.isEmpty()) return;

    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", file.errorString());
        return;
    }

    QTextStream out(&file);
    out << currentTextEdit->toPlainText();

    ui->editorTabs
    ->setTabText(
        ui->editorTabs->currentIndex(),
        filePath.section("/",-1,-1)
    );

    currentTab->setProperty("filePath", filePath);

    file.close();
}

void MainWindow::on_actionPrint_triggered()
{
    QWidget* currentTab = ui->editorTabs->currentWidget();

    if (currentTab == NULL) {
        QMessageBox::warning(this, "Warning", "No tab was selected");
        return;
    }

    QTextEdit* currentTextEdit =
    static_cast<QTextEdit*>(currentTab);

    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog qDialog(&printer, this);

    if (qDialog.exec() == QDialog::Rejected) {
        QMessageBox::warning(this, "Error", "Could not access Printer");
        return;
    }

    currentTextEdit->print(&printer);
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}


void MainWindow::on_actionCut_triggered()
{
    QWidget* currentTab = ui->editorTabs->currentWidget();

    if (currentTab == NULL) {
        QMessageBox::warning(this, "Warning", "No tab was selected");
        return;
    }

    QTextEdit* currentTextEdit =
    static_cast<QTextEdit*>(currentTab);

    currentTextEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    QWidget* currentTab = ui->editorTabs->currentWidget();

    if (currentTab == NULL) {
        QMessageBox::warning(this, "Warning", "No tab was selected");
        return;
    }

    QTextEdit* currentTextEdit =
    static_cast<QTextEdit*>(currentTab);

    currentTextEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    QWidget* currentTab = ui->editorTabs->currentWidget();

    if (currentTab == NULL) {
        QMessageBox::warning(this, "Warning", "No tab was selected");
        return;
    }

    QTextEdit* currentTextEdit =
    static_cast<QTextEdit*>(currentTab);

    currentTextEdit->paste();
}


void MainWindow::on_actionUndo_triggered()
{
    QWidget* currentTab = ui->editorTabs->currentWidget();

    if (currentTab == NULL) {
        QMessageBox::warning(this, "Warning", "No tab was selected");
        return;
    }

    QTextEdit* currentTextEdit =
    static_cast<QTextEdit*>(currentTab);

    currentTextEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    QWidget* currentTab = ui->editorTabs->currentWidget();

    if (currentTab == NULL) {
        QMessageBox::warning(this, "Warning", "No tab was selected");
        return;
    }

    QTextEdit* currentTextEdit =
    static_cast<QTextEdit*>(currentTab);

    currentTextEdit->redo();
}
