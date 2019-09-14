#include "IrcConnectionEditor.hpp"
#include "ui_IrcConnectionEditor.h"

namespace chatterino {

IrcConnectionEditor::IrcConnectionEditor(const IrcServerData &data, bool isAdd,
                                         QWidget *parent)

    : QDialog(parent, Qt::WindowStaysOnTopHint)
    , ui_(new Ui::IrcConnectionEditor)
    , data_(data)
{
    this->ui_->setupUi(this);

    this->setWindowTitle(QString(isAdd ? "Add " : "Edit ") + "Irc Connection");

    QObject::connect(this->ui_->userNameLineEdit, &QLineEdit::textChanged, this,
                     [this](const QString &text) {
                         this->ui_->nickNameLineEdit->setPlaceholderText(text);
                         this->ui_->realNameLineEdit->setPlaceholderText(text);
                     });

    this->ui_->serverLineEdit->setText(data.host);
    this->ui_->portSpinBox->setValue(data.port);
    this->ui_->securityCheckBox->setChecked(data.ssl);
    this->ui_->userNameLineEdit->setText(data.user);
    this->ui_->nickNameLineEdit->setText(data.nick);
    this->ui_->realNameLineEdit->setText(data.real);
    this->ui_->connectCommandsEditor->setPlainText(
        data.connectCommands.join('\n'));

    data.getPassword(this, [this](const QString &password) {
        this->ui_->passwordLineEdit->setText(password);
    });

    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    this->ui_->connectCommandsEditor->setFont(font);
}  // namespace chatterino

IrcConnectionEditor::~IrcConnectionEditor()
{
    delete ui_;
}

IrcServerData IrcConnectionEditor::data()
{
    auto data = this->data_;
    data.host = this->ui_->serverLineEdit->text();
    data.port = this->ui_->portSpinBox->value();
    data.ssl = this->ui_->securityCheckBox->isChecked();
    data.user = this->ui_->userNameLineEdit->text();
    data.nick = this->ui_->nickNameLineEdit->text();
    data.real = this->ui_->realNameLineEdit->text();
    data.connectCommands =
        this->ui_->connectCommandsEditor->toPlainText().split('\n');
    data.setPassword(this->ui_->passwordLineEdit->text());
    return data;
}

}  // namespace chatterino
