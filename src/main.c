#include "application.h"
#include "application_facade.h"

#include <puremvc/puremvc.h>
#include <gtk/gtk.h>

int main(const int argc, char **argv) {
    const char *name = "EmployeeAdmin";

    struct ModelMap **modelMap = (struct ModelMap *[]) {
        &(struct ModelMap){ .model = alloca(puremvc_model_size()) }, // Model Instance (Multiton Key)
        NULL
    };
    struct ProxyMap **proxyMap = (struct ProxyMap *[]) {
        &(struct ProxyMap){ .proxy = alloca(puremvc_proxy_size()) }, // UserProxy
        &(struct ProxyMap){ .proxy = alloca(puremvc_proxy_size()) }, // RoleProxy
        NULL
    };
    struct IModel *model = puremvc_model_getInstance(modelMap, name);
    model->initializeModel(model, proxyMap);

    struct ViewMap **viewMap = (struct ViewMap *[]) {
        &(struct ViewMap){ .view = alloca(puremvc_view_size()) }, // View Instance (Multiton Key)
        NULL
    };
    struct ObserverMap **observerMap = (struct ObserverMap *[]) { // ObserverMap for Notifications
        &(struct ObserverMap){ .observers = (struct IObserver *[]){ memset(alloca(puremvc_observer_size()), 0, puremvc_observer_size()), NULL } }, // STARTUP Notification Observers
        NULL
    };
    struct MediatorMap **mediatorMap = (struct MediatorMap *[]) {
        &(struct MediatorMap){ .mediator = alloca(puremvc_mediator_size()) }, // UserListMediator
        &(struct MediatorMap){ .mediator = alloca(puremvc_mediator_size()) }, // UserFormMediator
        &(struct MediatorMap){ .mediator = alloca(puremvc_mediator_size()) }, // UserRoleMediator
        NULL
    };
    struct IView *view = puremvc_view_getInstance(viewMap, name);
    view->initializeView(view, observerMap, mediatorMap);

    struct ControllerMap **controllerMap = (struct ControllerMap *[]) {
        &(struct ControllerMap){ .controller = alloca(puremvc_controller_size()) }, // Controller Instance (Multiton Key)
        NULL
    };
    struct CommandMap **commandMap = (struct CommandMap *[]) {
        &(struct CommandMap){}, // Command: StartupCommand
        NULL
    };
    struct IController *controller = puremvc_controller_getInstance(controllerMap, name);
    controller->initializeController(controller, view, commandMap); // Compose Controller with View and Commands

    struct FacadeMap **facadeMap = (struct FacadeMap *[]){
        &(struct FacadeMap){ .facade = alloca(puremvc_facade_size()) }, // Facade instance (Multiton Key)
        NULL
    };
    struct IFacade *super = application_facade_getInstance(facadeMap, name);
    super->initializeFacade(super, model, view, controller); // Compose Facade with Model, View, Controller
    const struct ApplicationFacade *facade = application_facade_bind(&(struct ApplicationFacade){}, super);

    struct Stage stage = {};
    facade->startup(facade, &stage);

    GtkApplication *app = getApp(&stage);

    const int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
