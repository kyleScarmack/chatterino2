#pragma once
#include "widgets/basewindow.hpp"

#include <QLabel>
#include <QWidget>
#include <pajlada/signals/signal.hpp>

namespace chatterino {
namespace widgets {

class TooltipWidget : public BaseWindow
{
    Q_OBJECT
public:
    TooltipWidget(BaseWidget *parent = nullptr);
    ~TooltipWidget();

    void setText(QString text);

    static TooltipWidget *getInstance()
    {
        static TooltipWidget *tooltipWidget = nullptr;
        if (tooltipWidget == nullptr) {
            tooltipWidget = new TooltipWidget();
        }
        return tooltipWidget;
    }

protected:
    virtual void changeEvent(QEvent *) override;
    virtual void leaveEvent(QEvent *) override;
    virtual void scaleChangedEvent(float) override;

private:
    QLabel *displayText;
    pajlada::Signals::Connection fontChangedConnection;

    void updateFont();
};

}  // namespace widgets
}  // namespace chatterino
