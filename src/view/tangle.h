#ifndef TANGLE_H
#define TANGLE_H

#include <QWidget>

namespace Ui {
class Tangle;
}

class Tangle : public QWidget
{
    Q_OBJECT

public:
    explicit Tangle(QWidget *parent = nullptr);
    ~Tangle();

private slots:
   void on_btn_generate_clicked();
   void on_btn_load_clicked();

private:
    Ui::Tangle *ui;
};

#endif // TANGLE_H
