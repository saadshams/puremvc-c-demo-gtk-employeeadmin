#include "application.h"
#include "application_facade.h"
#include "model/valueObject/user_vo.h"
#include "model/valueObject/role_vo.h"

#include <puremvc/puremvc.h>
#include <gtk/gtk.h>

int main(const int argc, char **argv) {
    const char *name = "EmployeeAdmin";

    // Model
    struct ModelMap **modelMap = (struct ModelMap *[]) {
        &(struct ModelMap) { .model = alloca(puremvc_model_size()) }, // Model Instance
        NULL
    };

    struct ProxyMap **proxyMap = (struct ProxyMap *[]) {
        &(struct ProxyMap) { .proxy = alloca(puremvc_proxy_size()) }, // UserProxy
        &(struct ProxyMap) { .proxy = alloca(puremvc_proxy_size()) }, // RoleProxy
        NULL
    };

    struct IModel *model = puremvc_model_getInstance(modelMap, name);
    model->initializeModel(model, proxyMap);

    // View
    struct ViewMap **viewMap = (struct ViewMap *[]) {
        &(struct ViewMap) { .view = alloca(puremvc_view_size()) }, // View Instance
        NULL
    };

    struct ObserverMap **observerMap = (struct ObserverMap *[]) { // ObserverMap for Notifications
        &(struct ObserverMap) {
            .observers = (struct IObserver *[]) { // STARTUP Notification Observers
                memset(alloca(puremvc_observer_size()), 0, puremvc_observer_size()), NULL
            }
        },
        &(struct ObserverMap) {
            .observers = (struct IObserver *[]) { // REGISTER Notification Observers
                memset(alloca(puremvc_observer_size()), 0, puremvc_observer_size()), NULL
            }
        },
        &(struct ObserverMap) {
            .observers = (struct IObserver *[]) { // USER_SELECTED Notification Observers
                memset(alloca(puremvc_observer_size()), 0, puremvc_observer_size()), NULL
            }
        },
        NULL
    };

    struct MediatorMap **mediatorMap = (struct MediatorMap *[]) {
        &(struct MediatorMap) { .mediator = alloca(puremvc_mediator_size()) }, // UserListMediator
        &(struct MediatorMap) { .mediator = alloca(puremvc_mediator_size()) }, // UserFormMediator
        &(struct MediatorMap) { .mediator = alloca(puremvc_mediator_size()) }, // UserRoleMediator
        NULL
    };

    struct IView *view = puremvc_view_getInstance(viewMap, name);
    view->initializeView(view, observerMap, mediatorMap);

    // Controller
    struct ControllerMap **controllerMap = (struct ControllerMap *[]) {
        &(struct ControllerMap) { .controller = alloca(puremvc_controller_size()) }, // Controller Instance
        NULL
    };

    struct CommandMap **commandMap = (struct CommandMap *[]) {
        &(struct CommandMap) {}, // StartupCommand
        &(struct CommandMap) {}, // RegisterCommand
        NULL
    };

    struct IController *controller = puremvc_controller_getInstance(controllerMap, name);
    controller->initializeController(controller, view, commandMap); // Compose Controller with View and Commands

    // Facade
    struct FacadeMap **facadeMap = (struct FacadeMap *[]) {
        &(struct FacadeMap){ .facade = alloca(puremvc_facade_size()) }, // Facade instance
        NULL
    };

    struct IFacade *super = application_facade_getInstance(facadeMap, name);
    super->initializeFacade(super, model, view, controller); // Compose Facade with Model, View, Controller
    struct ApplicationFacade *facade = application_facade_extend(&(struct ApplicationFacade){}, super);

    struct UserVO users[MAX_USERS] = {0};
    struct RoleVO roles[MAX_USERS] = {0};
    facade->startup(facade, (void *[]) { &users, &roles, NULL });

    GtkApplication *app = getApp(facade);
    const int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
