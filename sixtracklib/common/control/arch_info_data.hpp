

        class ArchInfoData
        {
            public:

            using status_t           = SIXTRL_CXX_NAMESPACE::arch_status_t;
            using arch_id_t          = SIXTRL_CXX_NAMESPACE::arch_id_t;
            using arch_flags_t       = uint16_t;
            using arch_init_fn_t     = status_t (*)( arch_id_t );
            using arch_shutdown_fn_t = status_t (*)( arch_id_t );

            explicit ArchInfoData(
                std::string const& SIXTRL_RESTRICT_REF
                    arch_info_str = std::string{},
                arch_flags_t const arch_flags = arch_flags_t{ 0 },
                arch_init_fn_t ptr_init_fn = nullptr,
                arch_shutdown_fn_t ptr_shutdown_fn = nullptr ) :
                m_arch_str( arch_info_str ), m_arch_flags( arch_flags ),
                m_init_fn( ptr_init_fn ), m_shutdown_fn( ptr_shutdown_fn )
            {

            }

            ArchInfoData( ArchInfoData const& ) = default;
            ArchInfoData( ArchInfoData&& ) = default;

            ArchInfoData& operator=( ArchInfoData const& ) = default;
            ArchInfoData& operator=( ArchInfoData&& ) = default;

            ~ArchInfoData() = default;

            bool isEnabled() const SIXTRL_NOEXCEPT
            {
                return ( ( ArchInfo::ARCH_ENABLED & this->m_arch_flags ) ==
                    this->m_arch_flags );
            }

            bool isInitialized() const SIXTRL_NOEXCEPT
            {
                return ( ( ArchInfo::ARCH_INITIALIZED & this->m_arch_flags ) ==
                    this->m_arch_flags );
            }

            bool isAvailable() const SIXTRL_NOEXCEPT
            {
                return ( ( ArchInfo::ARCH_AVAILABLE & this->m_arch_flags ) ==
                    this->m_arch_flags );
            }

            status_t initialize( arch_id_t const arch_id ) const
            {
                return ( this->m_init_fn != nullptr )
                    ? this->m_init_fn( arch_id )
                    : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;

            }

            status_t shutdown( arch_id_t const arch_id ) const
            {
                return ( this->m_shutdown_fn != nullptr )
                    ? this->m_shutdown_fn( arch_id )
                    : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
            }

            std::string         m_arch_str;
            arch_flags_t        m_arch_flags;
            arch_init_fn_t      m_init_fn;
            arch_shutdown_fn_t  m_shutdown_fn;
        };
