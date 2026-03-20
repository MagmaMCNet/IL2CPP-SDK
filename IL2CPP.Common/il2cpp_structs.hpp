#pragma once
#include <cstdint>
#include <string_view>
#include <type_traits>

namespace IL2CPP {

	extern "C" [[nodiscard]] __forceinline bool IsValid(const void* ptr) noexcept
	{
		if (!ptr) return false;
		constexpr uintptr_t minAddr = 0x10000;
		constexpr uintptr_t maxAddr = 0x7FFFFFFFFFFF;
		uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
		return addr >= minAddr && addr <= maxAddr;
	}

	[[nodiscard]] __forceinline void* Unbox(void* obj) noexcept
	{
		return static_cast<char*>(obj) + 0x10;
	}

	template<typename>
	struct is_const_member_fn : std::false_type {};

	template<typename R, typename C, typename... Args>
	struct is_const_member_fn<R(C::*)(Args...) const> : std::true_type {};

	struct il2cppFieldInfo;
	struct il2cppMethodInfo;
	struct il2cppClass;
	
	struct il2cppImage
	{
		const char* m_pName;
		const char* m_pNameNoExt;
	};

	struct il2cppAssemblyName
	{
		const char* m_pName;
		const char* m_pCulture;
		const char* m_pHash;
		const char* m_pPublicKey;
		unsigned int m_uHash;
		int m_iHashLength;
		unsigned int m_uFlags;
		int m_iMajor;
		int m_iMinor;
		int m_iBuild;
		int m_bRevision;
		unsigned char m_uPublicKeyToken[8];
		uint8_t _pad[4] = {};
	};

	struct il2cppAssembly
	{
		il2cppImage* m_pImage;
		unsigned int m_uToken;
		int m_ReferencedAssemblyStart;
		int m_ReferencedAssemblyCount;
		uint32_t _pad = 0;
		il2cppAssemblyName m_aName;
	};

#ifdef UNITY_VERSION_2022_3_8_HIGHER_
	struct il2cppType
	{
		void* data;
		unsigned int bits;
	};
#else
	struct il2cppType
	{
		union
		{
			void* m_pDummy;
			unsigned int m_uClassIndex;
			il2cppType* m_pType;
			void* m_pArray;
			unsigned int m_uGenericParameterIndex;
			void* m_pGenericClass;
		};
		unsigned int m_uAttributes : 16;
		unsigned int m_uType : 8;
		unsigned int m_uMods : 6;
		unsigned int m_uByref : 1;
		unsigned int m_uPinned : 1;
		uint32_t _pad = 0;
	};
#endif

	struct il2cppVirtualInvokeData
	{
		void* m_pMethodPointer;
		const il2cppMethodInfo* m_pMethod;
	};

	union il2cppRGCTXData
	{
		void* m_pDummy;
		const il2cppMethodInfo* m_pMethod;
		const il2cppType* m_pType;
		il2cppClass* m_pKlass;
	};

	struct il2cppRuntimeInterfaceOffsetPair
	{
		il2cppClass* m_pInterfaceType;
		int32_t m_iOffset;
		uint32_t _pad = 0;
	};

	struct il2cppClass
	{
		void* m_pImage;
		void* m_pGC;
		const char* m_pName;
		const char* m_pNamespace;
		il2cppType m_byvalArg;
		il2cppType m_thisArg;
		il2cppClass* m_pElementClass;
		il2cppClass* m_pCastClass;
		il2cppClass* m_pDeclareClass;
		il2cppClass* m_pParentClass;
		void* m_pGenericClass;
		void* m_pTypeDefinition;
		void* m_pInteropData;
		il2cppClass* m_pKlass;
		void* m_pFields;
		void* m_pEvents;
		void* m_pProperties;
		void* m_pMethods;
		il2cppClass** m_pNestedTypes;
		il2cppClass** m_ImplementedInterfaces;
		il2cppRuntimeInterfaceOffsetPair* m_pInterfaceOffsets;
		void* m_pStaticFields;
		il2cppRGCTXData* m_pRGCTX;
		il2cppClass** m_pTypeHierarchy;
		void* m_pUnityUserData;
		uint32_t m_uInitExceptionGCHandle;
		uint32_t m_uCCtorStarted;
		uint32_t m_uCCtorFinished;
		uint32_t _pad1 = 0;
		size_t m_uCCtorThread;
		void* m_pGenericContainerHandle;
		uint32_t m_uInstanceSize;
		uint32_t m_uActualSize;
		uint32_t m_uElementSize;
		int32_t m_iNativeSize;
		uint32_t m_uStaticFieldsSize;
		uint32_t m_uThreadStaticFieldsSize;
		int32_t m_iThreadStaticFieldDataOffset;
		uint32_t m_uFlags;
		uint32_t m_uToken;
		uint16_t m_uMethodCount;
		uint16_t m_uPropertyCount;
		uint16_t m_uFieldCount;
		uint16_t m_uEventCount;
		uint16_t m_uNestedTypesCount;
		uint16_t m_uVTableCount;
		uint16_t m_uInterfacesCount;
		uint16_t m_uInterfaceOffsetsCount;
		uint8_t m_uTypeHierarchyDepth;
		uint8_t m_uGenericRecursionDepth;
		uint8_t m_uRank;
		uint8_t m_uMinAlignment;
		uint8_t m_uNaturalAligment;
		uint8_t m_uPackingSize;
		uint8_t m_bInitialized : 1;
		uint8_t m_bEnumType : 1;
		uint8_t m_bNullable : 1;
		uint8_t m_bMarshaledFromNative : 1;
		uint8_t m_bSerializable : 1;
		uint8_t m_bBlittable : 1;
		uint8_t m_bIsImportOrWindow : 1;
		uint8_t m_bCCtor : 1;
		uint8_t m_bValueType : 1;
		uint8_t m_bIsAbstract : 1;
		uint8_t m_bIsInterface : 1;
		uint8_t m_bIsSealed : 1;
		uint8_t _pad2[4] = {};
		il2cppVirtualInvokeData m_vtable[255];
	};

	struct il2cppSystemType {
		il2cppClass* m_pClass = nullptr;
		void* m_pMonitor = nullptr;
	};

	struct il2cppFieldInfo
	{
		const char* m_pName;
		il2cppType* m_pType;
		il2cppClass* m_pParentClass;
		int m_iOffset;
		int m_iAttributeIndex;
		unsigned int m_uToken;
		uint32_t _pad = 0;
	};

	struct il2cppParameterInfo
	{
		const char* m_pName;
		int m_iPosition;
		unsigned int m_uToken;
		il2cppType* m_pParameterType;
	};

	struct il2cppMethodInfo
	{
		void* m_pMethodPointer;
		void* m_pVirtualMethodPointer;
		void* m_pInvokerMethod;
		const char* m_pName;
		il2cppClass* m_pClass;
		il2cppType* m_pReturnType;
		il2cppType** m_pParameters;

		union
		{
			void* m_pRGCTX;
			void* m_pMethodDefinition;
		};

		union
		{
			void* m_pGenericMethod;
			void* m_pGenericContainer;
		};

		unsigned int m_uToken;
		unsigned short m_uFlags;
		unsigned short m_uFlags2;
		unsigned short m_uSlot;
		unsigned char m_uArgsCount;
		unsigned char m_uGeneric : 1;
		unsigned char m_uInflated : 1;
		unsigned char m_uWrapperType : 1;
		unsigned char m_uMarshaledFromNative : 1;
		uint8_t _pad[4] = {};
	};

	struct il2cppPropertyInfo
	{
		il2cppClass* m_pParentClass;
		const char* m_pName;
		il2cppMethodInfo* m_pGet;
		il2cppMethodInfo* m_pSet;
		unsigned int m_uAttributes;
		unsigned int m_uToken;
	};

	struct il2cppArrayBounds
	{
		uintptr_t m_uLength;
		int m_iLowerBound;
		uint32_t _pad = 0;
	};

	struct il2cppObject {
		il2cppClass* m_pClass = nullptr;
		void* m_pMonitor = nullptr;

		// --- Non-inline methods (implemented in IL2CPP.Core) ---
		il2cppFieldInfo* GetFields(void** m_pIterator);
		il2cppMethodInfo* GetMethods(void** m_pIterator);

		il2cppFieldInfo* GetField(std::string_view m_pFieldName);
		il2cppMethodInfo* GetMethod(std::string_view m_pMethodName, int m_iArgs = -1);

		il2cppPropertyInfo* GetProperty(std::string_view m_pPropertyName);

		void* GetPropertyValue(std::string_view m_pPropertyName);
		void SetPropertyValue(std::string_view m_pPropertyName, void* m_tValue);
		void* GetMethodPointer(std::string_view m_pMethodName, int m_iArgs = -1);

		void* CallMethod_Impl(void* m_pMethod);
		void* CallMethod_Impl(void* m_pMethod, void* m_pArg);
		void* CallMethod_Impl(void* m_pMethod, void* m_pArg, void* m_pArg2);

		// --- Inline methods ---

		static __forceinline bool IsAlive(il2cppObject* obj) {
			return obj && obj->m_pClass;
		}

		template<typename T = void*>
		[[nodiscard]] __forceinline T* FieldByOffset(std::uintptr_t offset) {
			return reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(this) + offset);
		}
		template<typename T = void*>
		[[nodiscard]] __forceinline T _FieldByOffset(std::uintptr_t offset) {
			return *reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(this) + offset);
		}

		template<typename TReturn>
		TReturn CallMethod(void* m_pMethod) {
			return *reinterpret_cast<TReturn*>(CallMethod_Impl(m_pMethod));
		}

		template<typename TReturn, typename... TArgs>
		TReturn CallMethod(void* m_pMethod, TArgs... tArgs) {
			return *reinterpret_cast<TReturn*>(CallMethod_Impl(m_pMethod, tArgs...));
		}
		template<typename TReturn, typename... TArgs>
		TReturn CallMethod(std::string_view m_pMethodName, TArgs... tArgs) {
			void* method = GetMethodPointer(m_pMethodName);
			return CallMethod<TReturn>(method, tArgs...);
		}
		template<typename TReturn, typename... TArgs>
		TReturn CallMethodSafe(void* m_pMethod, TArgs... tArgs) {
			if (m_pMethod == nullptr) [[unlikely]]
				return TReturn{};
			return CallMethod<TReturn>(m_pMethod, tArgs...);
		}
		template<typename TReturn, typename... TArgs>
		TReturn CallMethodSafe(std::string_view m_pMethodName, TArgs... tArgs) {
			return CallMethodSafe<TReturn>(GetMethodPointer(m_pMethodName), tArgs...);
		}

		template<typename T>
		__inline T GetValue(int m_iOffset) {
			return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
		}
		template<typename T>
		__inline void SetValue(int m_iOffset, T m_tValue) {
			*reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + m_iOffset) = m_tValue;
		}

		template<typename T>
		T GetValue(il2cppFieldInfo* m_pField) {
			return GetValue<T>(m_pField->m_iOffset);
		}
		template<typename T>
		void SetValue(il2cppFieldInfo* m_pField, T m_tValue) {
			SetValue<T>(m_pField->m_iOffset, m_tValue);
		}

		template<typename T>
		T GetValue(std::string_view m_pMemberName) {
			il2cppFieldInfo* pField = GetField(m_pMemberName);
			if (pField) {
				if (pField->m_iOffset >= 0)
					return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + pField->m_iOffset);
			}
			else if (auto prop = GetProperty(m_pMemberName); prop && prop->m_pGet)
				return reinterpret_cast<T>(CallMethod_Impl(prop->m_pGet->m_pMethodPointer, nullptr));
			return T{};
		}
		template<typename T>
		void SetValue(std::string_view m_pMemberName, T m_tValue) {
			il2cppFieldInfo* pField = GetField(m_pMemberName);
			if (pField) {
				if (pField->m_iOffset >= 0) {
					*reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + pField->m_iOffset) = m_tValue;
					return;
				}
			}
			if constexpr (std::is_pointer_v<T>) {
				SetPropertyValue(m_pMemberName, const_cast<void*>(
					static_cast<const void*>(m_tValue)));
			}
			else {
				SetPropertyValue(m_pMemberName, reinterpret_cast<void*>(&m_tValue));
			}
		}
	};

} // namespace IL2CPP
