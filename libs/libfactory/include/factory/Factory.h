/**
 * @file Factory.h
 *
 * Provides classes which implement automatic registration of polymorphic types
 * from a name which identifies a subtype.  The code in this file has been
 * entirely taken from the SConfig library written by Andrea Lani and the
 * documentation and formatting has only been altered to match the standards
 * used in the Mutation++ library.  In addition, the use of exceptions has been
 * changed to match the Mutation++ exception policy.
 *
 * @author Andrea Lani
 * @author J.B. Scoggins
 */


#ifndef FACTORY_SPLIT_FACTORY_H
#define FACTORY_SPLIT_FACTORY_H

#include <string>
#include <map>
#include <sstream>
#include <vector>

template<class PTYPE>
class Provider;

/**
 * This class stores an archive of available Provider's for a generic
 * polymorphic type PTYPE. Once registered, they can be accessed by name.
 * This class is originally taken and modified from the VKI CoolFLUID package.
 */
template<class PTYPE>
class Factory {
  public:

    /**
     * Register a Provider.
     */
    void add(Provider<PTYPE> *p_provider) {
        typename std::map<std::string, Provider<PTYPE> *>::const_iterator it;
        it = m_providers.find(p_provider->getName());

        if (it==m_providers.end())
            m_providers[p_provider->getName()] = p_provider;
        else {
            std::stringstream s;
            s << "Provider <" << p_provider->getName() << "> has already "
              << "been registered for type " << PTYPE::typeName();
            throw std::runtime_error(s.str());
        }
    }

    /**
     * Get the provider corresponding to the given key.
     */
    Provider<PTYPE> *getProvider(const std::string &key) {
        typename std::map<std::string, Provider<PTYPE> *>::const_iterator it;
        it = m_providers.find(key);

        if (it!=m_providers.end())
            return dynamic_cast<Provider<PTYPE> *>(it->second);

        // Error because key is not a valid provider
        std::stringstream s;
        s << "Provider <" << key << "> for type " << PTYPE::typeName()
          << " is not registered.  Possible providers are:\n";
        for (it = m_providers.begin(); it!=m_providers.end(); it++)
            s << "  " << it->first << "\n";
        throw std::runtime_error(s.str());
    }

    /**
     * Instance of the singleton Factory.
     */
    static Factory<PTYPE> &getInstance() {
        static Factory<PTYPE> f;
        return f;
    }

    /**
     * Returns a pointer to an object of type registered by the given name.
     */
    static PTYPE *create(const std::string &name, typename PTYPE::ARGS args) {
        Provider<PTYPE> *p_provider = getInstance().getProvider(name);
        if (p_provider==NULL)
            return NULL;
        return p_provider->create(args);
    }

    /**
     * Returns a list of all object names registered to this factory.
     */
    static std::vector<std::string> names() {
        std::vector<std::string> names;
        typename std::map<std::string, Provider<PTYPE> *> &providers =
            getInstance().m_providers;
        typename std::map<std::string, Provider<PTYPE> *>::const_iterator iter;
        for (iter = providers.begin(); iter!=providers.end(); ++iter)
            names.push_back(iter->first);
        return names;
    }

  private:

    /**
     * Constructor.
     */
    Factory() = default;

    /**
     * Destructor.
     */
    ~Factory() = default;

  private: // data

    // archive of providers with type <name, Provider*>
    std::map<std::string, Provider<PTYPE> *> m_providers;

}; // class Factory


/**
 * This class provides a name to a deriving object.
 *
 * @author Andrea Lani
 */
class NamedObject {
  public:

    /**
     * Constructor.
     */
    explicit NamedObject(const std::string &name) : m_name(name) {}

    /**
     * Destructor.
     */
    ~NamedObject() = default;

    /**
     * Get the name of the object.
     */
    std::string getName() const {
        return m_name;
    }

  private:

    // name of the object
    std::string m_name;

}; // class NamedObject


/**
 * This class implements an object provider.
 *
 * @author Andrea Lani
 */
template<class PTYPE>
class Provider : public NamedObject {
  public:

    /**
     * Constructor.
     */
    explicit Provider(const std::string &name) : NamedObject(name) {
        Factory<PTYPE>::getInstance().add(this);
    }

    /**
     * Destructor.
     */
    virtual ~Provider() = default;

    /**
     * Create the chosen concrete object.
     */
    virtual PTYPE *create(typename PTYPE::ARGS args) = 0;

}; // class Provider


/**
 * This class implements a generic provider allowing client code to create
 * arbitrary types of polymorphic objects.
 *
 * @author Andrea Lani
 */
template<class CTYPE, class PTYPE>
class ObjectProvider : public Provider<PTYPE> {
  public:

    /**
     * Constructor.
     */
    explicit ObjectProvider(const std::string &name) : Provider<PTYPE>(name) {}

    /**
     * Destructor.
     */
    ~ObjectProvider() = default;

    /**
     * Create an object of polymorphic type PTYPE (parent) and static type
     * CTYPE (concrete).
     */
    PTYPE *create(typename PTYPE::ARGS args) {
        return new CTYPE(args);
    }

}; // class ObjectProvider

#endif //FACTORY_SPLIT_FACTORY_H
