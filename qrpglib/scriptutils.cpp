#include <QtCore>
#include <QtScript>
#include "scriptutils.h"
#include "globals.h"
#include "map.h"
#include "entity.h"
#include "npc.h"
#include "player.h"
#include "mapbox.h"

ScriptUtils::ScriptUtils() {  
  QScriptValue objectValue = scriptEngine->newQObject(this);
  scriptEngine->globalObject().setProperty("rpgx", objectValue);

  QScriptValue npcCtor = scriptEngine->newFunction(npcConstructor);
  QScriptValue metaObject = scriptEngine->newQMetaObject(&QObject::staticMetaObject, npcCtor);
  scriptEngine->globalObject().setProperty("Npc", metaObject);
}

void ScriptUtils::messageBox(QString s) {
  message(s);
}

void ScriptUtils::print(QString s) {
  cprint(s);
}

QScriptValue ScriptUtils::getEntity(QString s) {
  Entity * e = entities[mapentitynames[s]];
  return e->getScriptObject();
}

QScriptValue ScriptUtils::getMap() {
  return currentMap->getScriptObject();
}

QScriptValue ScriptUtils::teleport(QString map, int x, int y) {

}

QScriptValue ScriptUtils::player() {
  if(playerEntity)
    return playerEntity->getScriptObject();
  else
    return QScriptValue(QScriptValue::NullValue);
}

void ScriptUtils::setCamera(Entity * e) {
  mapBox->setCamera(e);
}
